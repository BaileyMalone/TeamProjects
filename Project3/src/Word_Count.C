//Word count implementation
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>

#include <string>
#include <vector>


#include "Word_Count.H"

using namespace std;


void Word_Count::add_word( std::string word )
{
  hashTable->Add( word, hashTable->Get(word) + 1 ); //Create new entry in hashTable with Word and count 1, since it's the first occurence.
}

int Word_Count::get_word_count( string word )
{
  return hashTable->Get(word);
}

//Sorting for the entry objects contained within the hashTable.
struct EntrySorter
{
  string root;
   bool operator() (HashTable< int >::Entry a, HashTable< int >::Entry b)
  {

    return  a.value > b.value; //Sort in ascending order.
  }

};

void Word_Count::get_top_words( vector< string > &word_list, vector< int > &counts, int count)
{

  vector< HashTable< int >::Entry > results =  hashTable->DumpEntries(); //Store all of the hash entries in results, temporarily.

  sort(results.begin(), results.end(), EntrySorter()); //Sort the results in Descending order.

   if ((int)results.size() >= count) {
     results.resize(count);  //Resize the results vector to N counts, where N is either 50, or the number specified by the -n arg.
   }

   //---- Add the Words and Counts to their respective vectors, sorted high to low ----//
   for(uint i = 0; i < results.size(); i++)
     {
       word_list.push_back(results[i].key); 
       counts.push_back(results[i].value);
     }

  
}

// TEST FOR WORD COUNT 
void get_word_count()
{
  // HashTable hash;
  // ifstream fin("testBook.txt");
  // string line;
  // int count;
  // int errCount;
  // while (fin.good())
  //   {
  //     hash.Add(line,count);
  //   }
  // cout << "Word_Count";
  // if (hash.Get("after")  ||
  //     hash.Get("over") ||
  //     hash.Get("through") ||
  //     hash.Get("such")   ||
  //     hash.Get("strictly")   ||
  //     hash.Get("details")   ||
  //     hash.Get("presume") ) {
  //   cerr << "Error!" << endl;
  // } else {
  //   cerr << "Done!" << endl;
  // }


}

/*
 *
 */
int Word_Count::NumberOfWords()
{ return hashTable->Occupancy(); }

vector<string> Word_Count::GetWords()
{
  return GetTable()->Keys();
}

HashTable<int> *Word_Count::GetTable()
{ return this->hashTable; }
