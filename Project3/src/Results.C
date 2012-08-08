//Results.C


#include <string>
#include <vector>
#include <sstream>


#include "Results.H"
#include "Page.H"
#include "HashTable.H"
#include "Output.H"

using namespace std;

bool Results::get(string url){
  return visited->Get(url);
}

void Results::add(string url){
  visited->Add(url, true);
  to_visit.push_back(url);
}
bool debug = true;//variable used to deterime if this class will cerr debug statements


void Results::print_all_vars()//a private method to print out all the member vars in this class for debugging
{
  cerr << "url_name: "            <<  url_name            << endl
       << "domain_name: "         << domain_name          << endl
       << "requested miss: "      << requested_miss       << endl 
       << "requested count: "     << requested_count      << endl 
       << "total_links: "         << total_links          << endl 
       << "total visits: "        << total_visits         << endl 
       << "total_wordcount: "     << total_wordcount      << endl 
       << "total_images: "        << total_images         << endl
       << "total_misspellings: "  << total_misspellings   << endl
       << "total_customers: "     << total_customers      << endl
       << "word_image_ratio: "    << word_image_ratio     << endl
       << "spelling_ratio: "      << spelling_ratio       << endl
       << "total_reviews: "       << total_reviews        << endl
       << "total_review_length: " << total_review_length  << endl
       << "total_cost: "          << total_cost           << endl
       << "ave_costs: "           << avg_cost             << endl
       << "total_stars: "         << total_stars          << endl
       << "ave_stars: "           << avg_stars            << endl
       << "avg_reviews: "         << avg_reviews          << endl
       << "median_reviews: "      << median_reviews       << endl
       << "max_reviews"           << max_reviews          << endl
       << "ms_per_review: "       << ms_per_customer      << endl
       << "ave_rlength: "         << avg_rlength          << endl;
}


Results::Results(string url, string domain){

  is_amazon_domain = (url.find("www.amazon.com") != string::npos);
 
  //initialize all the vars
  url_name = url;//set the url name
  domain_name = domain;//set the domain name
  requested_count = 100;//this is defaulted to 100 gets set in main
  requested_miss = 100; //this is defaulted to 100 gets set in main
  total_links = 0;
  total_visits = 0;
  total_wordcount = 0;
  total_images = 0;
  total_misspellings = 0;
  total_customers = 0;
  word_image_ratio = 0;
  spelling_ratio = 0;
  
  total_reviews = 0; total_review_length = 0;
  total_cost = 0; avg_cost = 0;
  total_stars = 0; avg_stars = 0;
  avg_reviews = 0; median_reviews = 0; max_reviews = 0;
  ms_per_customer = 0; avg_rlength = 0;

  visited = new HashTable<bool>();
  top_words = new Word_Count();
  top_misspelled = new Word_Count();
}

string Results::print_output(){
  if(total_images == 0){
    total_images = 1;//to keep word image ratio from throwing a floating point exception.
  }
  word_image_ratio = total_wordcount/total_images;//calculate the word image ratio to be used later
  Output out;//create the output object.
  vector<string> headers;//create the headers vector. for table headers
  string message;//for table description
  vector<HashTable<bool>::Entry > dump = visited->DumpEntries();// all the pages visited
  
  out.start_html(true);//start the html page

  headers.clear();//clear out the headers
  headers.push_back("pages visited");//set the headers for the table
  headers.push_back("avg words/image");
  headers.push_back("avg links/page");
  headers.push_back("avg misspellings/page");

  message = "The results of crawling";//set the message for the table
  out.start_table(3, headers,message);//start the table with option 3
  

  //add the entries to the table
  out.add_entry(total_visits);//add entry for total visits
  // may not be needed- out.add_entry(total_wordcount/total_images);//add entry for word to image ratio.  
  out.add_entry(word_image_ratio);//add entry for word to image ratio

  //**something here needs to be fixed to get total links for
  out.add_entry(total_links/total_visits);//add entry for total links to visits
  //**

  out.add_entry((double)total_misspellings/(double)total_visits);//add entry for ave misspelling per page
  out.end_table();//finnish this table

  if(is_amazon_domain)
    {
      headers.clear();//clear out the headers
      headers.push_back("avg number of reviews per person");//set the headers for the table
      headers.push_back("median reviews per person");
      headers.push_back("max reviews per person");
      headers.push_back("avg misspelling per person");
      headers.push_back("avg review length");
      headers.push_back("avg stars per review");
      
      message = "stats specific to amazon.com";//set the message for the table
      out.start_table(4, headers,message);//start the table with option 4

      
      //add the entries to the table
      out.add_entry(avg_reviews);//add entry for ave number of reviews.
      out.add_entry(median_reviews);//add entry for  median reviews per person
      out.add_entry(max_reviews);//add the entry for max reviews for a customer
      
      out.add_entry(ms_per_customer);//add entry for ave misspells per person

      out.add_entry(avg_rlength);//add entry for ave review lenght
      out.add_entry(avg_stars);//add entry for ave stars per customer
      out.end_table();//finnish this table

      //*** do some more extras**//

      headers.clear();//clear out the headers
      headers.push_back("total cost of all items found");//set the headers for the table
      headers.push_back("avg cost of item");
      headers.push_back("total customers found");


      message = "more stats specific to amazon.com";//set the message for the table
      out.start_table(4, headers,message);//start the table with option 4
      
      
      //add the entries to the table
      out.add_entry(total_cost);//add entry for ave number of reviews.
      out.add_entry(avg_cost);//add entry for  median reviews per person
      out.add_entry(total_customers);//add the entry for max reviews for a customer
      out.end_table();//finnish this table
      
    }

      //still need to ouput a lot of crap!!!
      //like top misspelled words for crawl.
      headers.clear();//clear out the headers
      headers.push_back("word");
      headers.push_back("count");
      headers.push_back("percent");
      headers.push_back("word");
      headers.push_back("count");
      headers.push_back("percent");
      
      //build the message with the number of requested words
      std::ostringstream ss;
      ss << "Top " << requested_miss << " misspelled words";
      message = ss.str();// set the message.

      //make the vectors to sent to word count
      vector<int> counts;
      vector<string> words;
      top_misspelled->get_top_words(words,counts, requested_miss);//get the words and counts
	//	int actual_count = word.size(); //the actual number of words to be printed out could be less than requested.
      out.start_table(1, headers, message);//start table with option one for spell check
      //iterate through words adding to the table.
      for(size_t i = 0; i < words.size(); i++)
	{
	  out.add_entry(words [i]);
	  out.add_entry(counts[i]);
	  out.add_entry((double)counts[i]/(double)total_wordcount);
	}
     
      out.end_table();//end misspelled words table.
      
      //and total word count
      //headers are the same.
      //clear words and counts for top words.
      counts.clear();
      words.clear();
      top_words->get_top_words(words, counts, requested_count);//get the words and counts 
      
      //build the message with the number of requested words
      ss.str("");
      ss << "Top " << requested_count << " found for crawl";
      message = ss.str();// set the message.
      out.start_table(2, headers, message);//start with option2 for word count.
      //iterate through the wordcount and add to the table.
      for(size_t i = 0; i < words.size(); i++)
	{
	  out.add_entry(words [i]);
	  out.add_entry(counts[i]);
	  out.add_entry((double)counts[i]/(double)total_wordcount);
	}
      
      out.end_table();//end total words table.
      
      out.end_html();//finnish up the webpage
      
      if(debug)//this prints out the debugs if desired
	{
	  cerr << "***debugging out from Results.C L:190***" << endl;//let them know were these are coming from
	  print_all_vars();//print out all the vars.
	  cerr << "***End debugging out from Results.C***" << endl;//let them know thats all this is going to print out.
	}

  return "";
}




