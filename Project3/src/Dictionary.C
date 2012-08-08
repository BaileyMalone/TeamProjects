/*
 * Dictionary.C
 * Team: Exception
 * Date: Spring 2012
 *
 */
#include <stdio.h>
#include <iostream>
#include <locale>
#include <fstream>

#include "Dictionary.H"

using namespace std;
/*---------------Constructor-----------------*/
Dictionary::Dictionary( string file_name ) 
{
  
  hashTable = new HashTable<int>();

  //cerr << file_name << endl;
  //Initialize data structures below:

  CreateHashTable(file_name);
  //cerr << "$$$ HashTable Created $$\n";
}

/* DEBUG */
int Dictionary::Size()
{ return hashTable->Occupancy(); }
// //Best matches
// bool Dictionary::best_matches( string word, vector<string> &list, int count)
// {
//   //Compare word against the BKTree, looking for similar entries. Update the vector list 
//   //with up to 'count' suggested matches.
//   if(!spelled_correctly(word))
//       {
// 	list = hashTable->get(word, count);
// 	return false;
//       }
//   else
//     {
//       return true;
//     }
// }

//Spell check
bool Dictionary::spelled_correctly( string word )
{
  return hashTable->Get(word); //Determine if the word exists in hashTable
}



void Dictionary::CreateHashTable(string file_name)
{
  ifstream fin(file_name.c_str());
  string line;

  //---- Build the Hash Table from file ----//
  while (getline(fin, line))
    {
      fin >> line;
      /* DEBUG */
      // cout << "string_read_in " << line << "\n";

      hashTable->Add(line, 1); //Add line to hash table.
      
      /* DEBUG */
//       cout << "checking_file_stream\n";
//       cout << "fin.good() ~ " << fin.good() << "\n";
//       cout << "fin.eof() ~ " << fin.eof() << "\n\n";
    }

  fin.close();
 
}

/*-----------------TESTS----------------------*/
//No tests here.
//EOF
