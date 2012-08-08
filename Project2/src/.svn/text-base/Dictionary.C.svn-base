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
  
  tree = new BKTree(); 
  hashTable = new HashTable<int>();


  cerr << file_name << endl;
  //Initialize data structures below:
#ifdef HASHTABLE
  CreateHashTable(file_name);
  cerr << "$$$ HashTable Created $$\n";
#else
  CreateBKTree(file_name);
  cerr << "$$$ BKTree Created $$\n";
#endif


}


//Best matches
bool Dictionary::best_matches( string word, vector<string> &list, int count)
{
  //Compare word against the BKTree, looking for similar entries. Update the vector list 
  //with up to 'count' suggested matches.
  if(!spelled_correctly(word))
      {
	list = tree->get(word, count);
	return false;
      }
  else
    {
      return true;
    }
}

//Spell check
bool Dictionary::spelled_correctly( string word )
{
#ifdef HASHTABLE
  return  hashTable->Get(word); //Determine if the word exists in hashTable
#else
  return tree->contains( word );  //Check the tree if HashTable isn't defined. Mostly for debug purposes.
#endif
}



void Dictionary::CreateHashTable(string file_name)
{
  ifstream fin(file_name.c_str());
  string line;

  //---- Build the Hash Table from file ----//
  while (getline(fin, line))
    {
      /* DEBUG */
      // cout << "Next Add()...\n";


      fin >> line;
      /* DEBUG */
      // cout << "string_read_in " << line << "\n";

      hashTable->Add(line, 0); //Add line to hash table.
      
      /* DEBUG */
//       cout << "checking_file_stream\n";
//       cout << "fin.good() ~ " << fin.good() << "\n";
//       cout << "fin.eof() ~ " << fin.eof() << "\n\n";
    }


 
}


void Dictionary::CreateBKTree(string file_name)
{


  ifstream fin(file_name.c_str(), ifstream::in);  
  while(fin.good())
    {
      string line;
      fin >> line;
      tree->add(line);  //Create new node in BKTree for every string in file
    }
}



/*-----------------TESTS----------------------*/
void test_spelled_correctly()
{
  Dictionary dic("testwords.txt");
  cout << "Testing for spelling...";
  if(!dic.spelled_correctly("merch") ||
     dic.spelled_correctly("merestt"))
    {
      cout << "Error!" << endl;
    }
  else
    {
      cout << "Done!" << endl;
    }

}


void test_best_matches()
{
  Dictionary dic("testwords.txt");
  vector<string> t1;
  vector<string> t2;

  //Wat do?
    cout << "Testing for best matches...";
    dic.best_matches("merchh", t1, 5);
    dic.best_matches("tesst", t2, 5);

    if(t1.size() < 1 || t2.size() < 1)
    {
	cout << "Error!" << endl;
	cout << t1.size() << " " << t2.size() << endl;
	 }
    else
      {
	cout << "No Problems!" << endl;
	for(unsigned int i = 0; i < t1.size(); i++)
	  cout << t1.at(i) << endl;
	for(unsigned int i = 0; i < t2.size(); i++)
	  cout << t2.at(i) << endl;
      }
}
//EOF
