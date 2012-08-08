//main.C

#include <signal.h>
#include <cstdlib>
#include <string>
#include <cstring>
//#include <vector>
#include <curl/curl.h>
#include <iostream>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

//Dictionary includes
//#include "HashTable.H"

//#include "Dictionary.H"

//Crawler includes
#include "map.H"
#include "reduce.H"
#include "Results.H"
#include "RateLimiter.H"


using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

bool time_to_die = false;
boost::condition work_ready;
boost::mutex results_mutex;
RateLimiter limit(8);
int busy_threads = 0;
Results *result_ptr;

Dictionary d("words.txt");

 
bool int_option(int argc, const char** argv, const char* name, int &out, int default_val=0) {
  for (int i = 1; i < argc - 1; i++) {
    if (0 == strcmp(argv[i]+1, name)) {
      out = atoi(argv[i+1]);
      return true;
    }
  }
  out = default_val;
  return false;
}

bool str_option(int argc, const char** argv, const char* name, string &out, string default_val="") {
  for (int i = 1; i < argc - 1; i++) {
    if (0 == strcmp(argv[i]+1, name)) {
      out = argv[i+1];
      return true;
    }
  }
  out = default_val;
  return false;
}

void test_option_parsing()
{
  int argc = 7;
  const char* argv[] = {"test", "-int", "5", "-int2", "7",  "-str", "Hallo.There"};
  int int1;
  int int3;
  string hallo;
  string world;
  bool found_passed = int_option(argc, argv, "int", int1) && 
    !int_option(argc, argv, "int3", int3, 9) &&
    str_option(argc, argv, "str", hallo) &&
    !str_option(argc, argv, "str2", world, "Woild");

  bool default_passed = int3 == 9 && world == "Woild";

  bool val_passed = int1 == 5 && hallo == "Hallo.There";

  cerr << ((found_passed && default_passed && val_passed) ? "Passed!" : "Failed!") << endl;
}

void run_tests()
{
  test_option_parsing();
  test_ratelimiter();
}

/*
 *Signal interruption callback. Upon receiving a Ctrl-C the crawler's progress will be serialized for later resuming.
 */
void sigproc(int param){
  if (time_to_die)
  {
    boost::mutex::scoped_lock lock(results_mutex);
    cerr << "Impatient type, huh?  I'll see what I can do." << endl;
    result_ptr->print_output();
    exit(-1);
  } else {
    cerr << "Signal interrupt... Saving crawler state" << endl;
    time_to_die = true;
    work_ready.notify_all();
  }
}

void crawl_worker()
{
  while (1) {
    string url;
    {
      // Lock results
      boost::mutex::scoped_lock lock(results_mutex);

      // Wait for work
      while (result_ptr->to_visit.empty() && !time_to_die) {
        
        // If no more work is coming, the we are no longer needed
        if (busy_threads == 0) {
          cerr << "No more work" << endl;
          return;
        }

        work_ready.wait(lock);
      }

      if (time_to_die) {
        cerr << "Like tears in the rain.  Time to die." << endl;
        return;
      }

      // Get work
      url = result_ptr->to_visit.back();
      result_ptr->to_visit.pop_back();
      cerr << "Found some work: " << url << endl;

      busy_threads++;
      cerr << "Now running on " << busy_threads << " cylinders" << endl;
    }
    
    // Do work
    Page* page = Map(url, limit, d);
    if (page)
    {
      // Lock results
      boost::mutex::scoped_lock lock(results_mutex);
      cerr << "Reducing" << endl;
      reduce(page, *result_ptr);

      delete page;
    }
    busy_threads--;
    // Notify threads
    cerr << "A new batch of work is ready" << endl;
    work_ready.notify_all();
  }
}

int main(int argc, const char* args_list[])
{
  for (int i = 0; i < argc; i++) {
    if (0 == strcmp(args_list[i], "-t")) {
      run_tests();
      return 0;
    }
  }
  string url;
  bool just_url;
  string domain;
  int threads;
  int count;
  int miss;


  url = args_list[1];
  just_url = !str_option(argc, args_list, "domain", domain);
  int_option(argc, args_list, "threads", threads, 1);
  int_option(argc, args_list, "count", count, 100);
  int_option(argc, args_list, "miss", miss, 100);

  if (threads > 8) {
    cerr << "Warning: Maximum number of threads is 8.  Only using 8 threads." << endl;
    threads = 8;
  }

  Results result(url, domain);
  result_ptr = &result;
  vector<Page> pages;
  result.requested_count = count;
  result.requested_miss = miss;
  signal(SIGINT, sigproc);

  if (just_url) {
    cerr << "Just grabbing " << url << endl;
    Page *page = Map(url, limit, d);

    if(page){
    reduce(page, result);
    delete page;
    }
  } else {
    cerr << "Crawling " << domain << " starting with " << url << endl;
    //    Results result;
    result.to_visit.push_back(url);
    vector<boost::thread*> thread_vec;
    for (int i = 0; i < threads; i++) {
      thread_vec.push_back(new boost::thread(crawl_worker));
    }
    for (unsigned int i = 0; i < thread_vec.size(); i++) {
      cerr << "Waiting for thread" << endl;
      thread_vec[i]->join();
      delete thread_vec[i];
      thread_vec[i] = 0;
    }
  }

  {
    boost::mutex::scoped_lock lock(results_mutex);
    result.print_output();
  }
  return 0;
}



