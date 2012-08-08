/*
 * page.H
 */
#ifndef PAGE_H_
#define PAGE_H_

/*
 * Team: Exception
 * Date: Spring 2012
 * Description: page class
 * 
 * what does this do?
 */

#include "AmazonCustomer.H"
#include "Word_Count.H"



// Class or struct, whatevs.
class Page
{
  //friend class Results; // will let results poke my privates!
  //friend void reduce( vector<Page>, Results&);

  Word_Count *BadWords;
  Word_Count *Histogram;
  std::vector<std::string> list_of_links;
  std::string url;
  int image_counter;

  //int wordCounter; //Possibly retype these as Hash Maps, and initialize them for counting words.
  //  HashTable<int> wordCounter;
  //  HashTable<int> misspellings;

  // Keeps track of the number of reviews seen on each page.
  // For the ave length of review extra and average stars per customer. 
  int number_reviews;

private:
  // Keeps track of the length of all reviews seen on page.
  // For the ave length of review extra.
  int sum_of_review_counts; 

  // Keeps track of total number of stars per page.
  // For the ave stars per customer extra
  int sum_of_stars;

  // NEW
  // All of the reviewers for an amazon.com page
  std::vector<AmazonCustomer> reviewers;

public:
  int NumberOfProfilePages; /* For Debugging! */


public:
  Page() 
  {
    this->Histogram = 0;
    this->BadWords = 0;
    this->number_reviews = 0;
    this->image_counter = 0;
    this->sum_of_review_counts = 0;
    this->sum_of_stars = 0;
  }
  Page(std::string s)
  { this->url = s;
    this->image_counter = 0;
    this->number_reviews = 0;
    this->sum_of_review_counts = 0;
    this->sum_of_stars = 0;
  }

  ~Page();

  bool isAmazonPage;
  std::vector<std::string> GetLinks();
  std::string Url();
  Word_Count *GetHistogram();
  Word_Count *GetMisspellings();
  int GetImageCount();
  std::vector<AmazonCustomer> GetReviewers();
  void SetLinks(std::vector<std::string> links);
  void SetBadWords(Word_Count *misspellings);
  void SetHistogram(Word_Count *histogram);
  void SetImageCount();
  void SetReviewers(std::vector<AmazonCustomer> revs);
  

};

#endif
