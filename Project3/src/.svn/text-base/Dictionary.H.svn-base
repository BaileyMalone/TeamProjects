#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <string>
#include <vector>

#ifndef HASHTABLE
#include "HashTable.H"
#endif

//#include "Output.H"

/*
 * Team: Exception
 * Date: Spring 2012
 * Description: Dictionary class
 * 
 * Dictionary takes a string representing the file name to be read in.
 * Builds two data structures, a BKTree and a HashTable. The Tree is used for fuzzy string matches and provides suggestions for any incorrect word found in a file.
 * spelled_correctly checks if a given word exists in the HashTable, if it does not, the word must be spelled wrong, or it doesn't exist in the current dictionary file.
 */

class Dictionary
{
public:
  Dictionary( std::string file_name ); // read the file and create the dictionary.
  ~Dictionary() {
    delete hashTable;
  }
  bool spelled_correctly( std::string word );
  bool best_matches( std::string word, std::vector<std::string> &list, int count ); // return true if spelled correctly or up to count (default 5) best matches
  int Size();
  
private:

  void CreateHashTable(std::string file_name);

  HashTable<int> *hashTable;
};
void test_spelled_correctly(); //Tests
void test_best_matches(); //More tests

#endif /* _DICTIONARY_H_ */
