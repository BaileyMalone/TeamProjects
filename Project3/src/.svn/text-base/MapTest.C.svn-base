//#include "page.H"
//#include "Word_Count.H"
#include <stdio.h>
#include <string>
#include "RateLimiter.H"
#include "map.H"

//using namespace std;



int main()
{
  //string url("http://www.amazon.com/");
  std::string a("http://www.amazon.com/Turtle-Beach-Call-Duty-Playstation-3/");
  std::string b("dp/B005EEMYCO/ref=sr_1_7?ie=UTF8&qid=1329798456&sr=8-7");
  //std::string a("http://www.amazon.com/dp/B002GYWHSQ/?tag=googhydr-");
  //std::string b("20&hvadid=16413069595&ref=pd_sl_1gtlqzgaj7_b");
  std::string c = a.append(b);
  //std::string c("http://eng.utah.edu/~ccurtis/page1.html");
  std::string url(c);
            
  std::string filename ("words.txt");
  Dictionary dic(filename);

  RateLimiter limiter(8);

  /* DEBUG */
  printf("Calling Map!\n");

  Page *page =  Map(url, limiter, dic);
  //Page page = Map(url, dic);

  //printf("Page URL: %s\n", page.Url().c_str());
  printf("<<Map has Finished Running>>\n");


  std::vector<std::string> links = page->GetLinks();

  //std::vector<string>::iterator it;
  //cout << "Links: \n \n" << endl;
  //for (it = links.begin(); it < links.end(); ++it)
    //cout << "link ~ " <<  *it << "\n\n" << endl;


  /* Set up Page's Histogram */
  Word_Count *histogram = page->GetHistogram();
      // Print the Histogram
  printf("Page has %i total English words!\n", histogram->NumberOfWords());
  std::vector<std::string> words = histogram->GetWords();
  printf("There are %i misspellings!\n", 
	 page->GetMisspellings()->NumberOfWords());

 
  std::vector<AmazonCustomer> customers = page->GetReviewers();

  std::vector<AmazonCustomer>::iterator it;
  std::vector<std::pair <double, double> >::iterator it2;
  printf("\nPage has %i images\n\n", page->GetImageCount());
  printf("\nReviewers: \n\n");
  double x;
  std::vector <std::pair <double, double> > pairs;
  for (it = customers.begin(); it < customers.end(); ++it)
    {
      x = ((double)(*it).length_of_reviews/(*it).number_of_reviews);
      printf(" ~ %s\n", (*it).name.c_str());
      printf("Total Words = %i\n", (*it).length_of_reviews);
      printf("Has %i total reviews.\n", (*it).number_of_reviews);
      printf("With an average review length of %f words.\n", x);
      printf("And %i misspellings.\n\n", (*it).misspellings_count);

      printf("Max Review Length of %i\n", (*it).max_review_length);

      pairs = (*it).stars_cost;
      int j = 0;
      for (it2 = pairs.begin(); it2 < pairs.end(); ++it2)
	{
	  printf("(Stars, Cost) = (%f, %f)\n",
		 pairs.at(j).first, pairs.at(j).second);
	  j += 1;
	}
    }



  return 0;
}
