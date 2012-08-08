#ifndef AMAZONCUSTOMER_H_
#define AMAZONCUSTOMER_H_
#include <map>
#include <vector>
#include <utility>
#include <string>

/*
 * Team: Exception
 * Date: Spring 2012
 * Description: AmazonCustomer class
 * 
 * what does this do?
 */

//using namespace std;

class AmazonCustomer
{
public:
  std::string name;
  int misspellings_count;
  int number_of_reviews;
  int length_of_reviews;
  int max_review_length;
  
  //int avg_review_length;
  // Map: (star-rating, price of item)
  std::vector <std::pair <double, double> > stars_cost;
    

  AmazonCustomer(std::string s)
  { 
    this->name = s; 
    this->misspellings_count = 0;
    this->length_of_reviews = 0;
  }
};
#endif 
