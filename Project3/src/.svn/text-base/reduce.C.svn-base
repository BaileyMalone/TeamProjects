/* 
 * reduce.C
 */
#include <vector> 
#include <string>

#include "reduce.H"
#include "Page.H"

using namespace std;


/**
 * Small helper function to determine if a URL exists within the given domain.
 * This is to prevent venturing outside of the domain.
 */
bool is_good_url(string url, string domain){
  if(domain.empty())
    return true;
  else
    return url.find(domain) != string::npos;
}

void reduce(Page *page, Results& ro ){  

  /**Less nasty iterator loop
   *Search through the vector of Page objects, and for every page object, iterate through its list of 
   *links. For every URL contained within LoL, if it hasn't been visited, add it to Result's Hash.
   This prevents the same URL being visited multiple times.
  */
  ro.total_visits++;	
  vector<string> links = page->GetLinks();
  ro.total_links+= links.size();//increment the total links variable by the links found on current page.
  for(vector<string>::iterator j = links.begin(); j != links.end(); j++){
    if(!ro.get(*j) && is_good_url(*j, ro.domain_name)){
      ro.add(*j);

    }
  }

  //This updates the totals for image count, misspellings, word count, and customers found.
  ro.total_images += page->GetImageCount();
  //ro.total_misspellings += page->GetMisspellings()->NumberOfWords();
  //ro.total_wordcount += page->GetHistogram()->NumberOfWords();
 
 
  //Iterate through both Word_Count objects, obtain a list of all words in each, and add them to the results word_count object(s).
  //This will maintain a count of all words throughout the crawl process.
  vector<string> hist = page->GetHistogram()->GetWords();
  vector<string> miss = page->GetMisspellings()->GetWords();

  for(vector<string>::iterator word = hist.begin(); word != hist.end(); word++){
    int j = page->GetHistogram()->get_word_count(*word);
    for (int i = 0; i < j; i++){
      ro.top_words->add_word(*word);
    }
  }

  for(vector<string>::iterator word = miss.begin(); word != miss.end(); word++){
    int j = page->GetMisspellings()->get_word_count(*word);
    for (int i = 0; i < j; i++){
      ro.top_misspelled->add_word(*word);
    }
  }

  ro.total_wordcount = 0;
  ro.total_misspellings = 0;
  vector<string> tothist = ro.top_words->GetWords();
  vector<string> totmiss = ro.top_misspelled->GetWords();
  for(vector<string>::iterator word = tothist.begin(); word != tothist.end(); word++){
    ro.total_wordcount += ro.top_words->get_word_count(*word);
  }

  for(vector<string>::iterator word = totmiss.begin(); word != totmiss.end(); word++){
    ro.total_misspellings += ro.top_misspelled->get_word_count(*word);
  }
  //If the curent page object is an amazon page...
  if(page->isAmazonPage){

    int customer_misspellings = 0;
    ro.total_customers += page->GetReviewers().size();
    //Iterate through the vector of AmazonCustomer objects, and obtain pertinent information from each customer.
    vector<AmazonCustomer> customers = page->GetReviewers();
    for(vector<AmazonCustomer>::iterator cust = customers.begin(); cust != customers.end(); cust++){

      if(ro.max_reviews < (*cust).number_of_reviews){
	ro.max_reviews = (*cust).number_of_reviews;
	ro.median_reviews = (*cust).number_of_reviews / 2;
      }

      ro.total_reviews += (*cust).number_of_reviews;
      customer_misspellings += (*cust).misspellings_count;
      ro.total_review_length += (*cust).length_of_reviews;
      //Iterate through the pair of stars and cost, and add update the totals for each.
      for(vector<pair <double, double> >::iterator k = (*cust).stars_cost.begin(); k != (*cust).stars_cost.end(); k++){
        ro.total_stars += k->first;
        ro.total_cost += k->second;
      }
    }

    //Find the averages for all bits of data above:
    ro.ms_per_customer = (double) customer_misspellings / (double) ro.total_reviews;
    ro.avg_rlength = (double) ro.total_review_length / (double)ro.total_reviews;
    ro.avg_stars = (double) ro.total_stars / (double)ro.total_reviews;
    ro.avg_cost  = (double) ro.total_cost / (double)ro.total_visits;
    ro.avg_reviews = (double)ro.total_reviews / (double)ro.total_customers;
    
    //ro.ms_per_customer = (double)ro.total_misspellings / (double) ro.total_reviews;
  }
 

}


