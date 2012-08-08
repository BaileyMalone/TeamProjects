/*
 * Map.H
 */
#ifndef MAP_H_
#define MAP_H_

//#include <vector>
#include "Page.H"
#include "Dictionary.H"
#include "RateLimiter.H"
//#include "AmazonCustomer.H"
//#include "Word_Count.H"

//using namespace std;


/*
 * Map() is part of a Map-Reduce parrallelism structure.
 * Map takes in a single URL and creates (and returns) 
 * a "Page Object" representing a web page crawled.
 *
 * The List of Links are used by Reduce() to continue the
 * architecture.
 */
Page *Map(std::string url, RateLimiter &rl, Dictionary &dic);
//Page Map(std::string url, Dictionary &dic);
size_t grab_HTML_src(void *ptr, size_t size, size_t n, void *data);
void parse_links(std::string data, std::vector<std::string>* links);
void get_english(std::string data, Word_Count* english);
bool IsPunctuation(char c);
void tokenize(std::string s, Word_Count *words);

    
#endif
