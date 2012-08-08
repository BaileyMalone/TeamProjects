#ifndef _WORD_COUNT_H_
#define _WORD_COUNT_H_

#include "HashTable.H"
/**
  * Word count is used for keeping track of all words in a file, including the most correctly and incorrectly spelled words.
  *
  * add_word adds a word into the hash upon first encounter. Every subsequent encounter of 'word' the counter is incremented by one, 
  *   giving an accurate word count for every word in a file.
  *
  * get_word_count returns the total count of any particular word in a file.
  *
  *  get_top_words populates the &word_list and &counts with the top 'count' most used words.
  */

class Word_Count
{
 public:

  void add_word( std::string word ); //Add a word to the Hash Table
  int get_word_count( std::string word); //Get the word count 
  void get_top_words( std::vector<std::string> &word_list, std::vector<int> &counts, int count=50); // return separate lists (in descending order) of most frequent words.

 private:

  HashTable<int> hashTable; //HashTable of integers used for tracking counts.

}; 

void get_word_count();
#endif /* _WORD_COUNT_H_ */
