//Results.H
#ifndef RESULTS_H_
#define RESULTS_H_

/*
 * Team: Exception
 * Date: Spring 2012
 * Description: Results class
 * 
 * what does this do?
 */

//**commented out so this sob compiles**//
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>

#include "HashTable.H"
#include "Page.H"
#include "Word_Count.H"


class Results{

  HashTable<bool> *visited;

private:
  //**commented out so this sob compiles**//
//   friend class boost::serialization::access; 
//   template<class Archive> 
//   void serialize(Archive & ar, const uint version) 
//   { 
//     ar & visited; 
//     ar & to_visit; 
//   } 
 public:

  Results(std::string url, std::string domain);
  ~Results() {
    delete visited;
    visited = 0;
    delete top_words;
    top_words = 0;
    delete top_misspelled;
    top_misspelled = 0;
  }
  //a method soley for debugging. cerr's all the member vars in Results.
  void print_all_vars();

  std::vector<std::string> to_visit;
  bool get(std::string url);  
  void add(std::string url);
  std::string print_output();
  std::string amazon_output();

  //Goodies go here.
  bool is_amazon_domain;
  std::string url_name;
  std::string domain_name;

  //**
  int total_links;//this is a count of all the links on all the pages crawled
  //including repeats. currently we don't have this but we need it.
  //**
  int requested_count;    // for specifying how many words in the counts the user wants to see
  int requested_miss;     // for specifying how many misspelled words the user wants to see
  int total_visits;       // fpr storing the total webpages the crawler has visited
  int total_wordcount;    // for storing a count of all  words the crawler has seen including repeats.
  int total_images;       // for storing a count of all  images the crawler has seen.
  int total_misspellings; // for storing a count of all the misspelling the crawler has seen including repeats.
  int total_customers;    // for storing a count of all amazon customers the crawler has seen.
  double word_image_ratio;// words/images
  double spelling_ratio;  // misspellings/words
  Word_Count *top_misspelled;//ref to a word count object that stores misspelled words and thier counts
  Word_Count *top_words;//ref to a word count object that stores words and thier counts
  //End goodies.


  //Amazon Extras go here:
  int total_reviews, total_review_length;
  double total_cost, avg_cost;
  double total_stars, avg_stars;
  double avg_reviews, median_reviews, max_reviews;
  double ms_per_customer, avg_rlength;
  
  

};
#endif
