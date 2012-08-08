/*
 * main.C
 * Team: Exception
 * Date: Spring 2012
 *
 */
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <locale>
#include <ctype.h>
#include <cstdlib>
#include <cstring>

#include "Dictionary.H"
#include "BKTree.H"
#include "Output.H"
#include "Word_Count.H"

void test_hashtables()
{
  
  cerr << "Testing HashTable..." << flush;
  HashTable<int> h;
  h.Add("word", 5);
  h.Add("test", 4);
  h.Add("mercers", 3);
  if(!(h.Get("word") && *h.Get("word") == 5) ||
     h.Get("tset"))
    cerr << "Error!" << endl;
  else
    cerr << "Done!" << endl;
}

int run_tests()
{
  test_bktrees();
  test_hashtables();
  return 0;
}

int main(int arg_count, char *args_list[]) 
{
  string dictionary_file("words"); // Name of dictionary file.
  int n = 50; // Default count for top words.
  bool file_list_parsing = false;
  vector<string> files;

  //---- Input argument handlers ----//
  for (int i = 1; i < arg_count; i++) {
    if (0 == strcmp("-t", args_list[i])) {
      return run_tests();
    } else if (0 == strcmp("-d", args_list[i])) {
      if (i == arg_count - 1) {
	cerr << "-d must be followed by a file name" << endl;
	return -1;
      }
      dictionary_file = args_list[i+1];
      file_list_parsing = false;
    } else if (0 == strcmp("-n", args_list[i])) {
      if (i == arg_count - 1) {
	cerr << "-n must be followed by a non-zero number" << endl;
	return -1;
      }
      n = atoi(args_list[i+1]);
      if (n == 0) {
	cerr << "-n must be followed by a non-zero number" << endl;
	return -1;
      }
      file_list_parsing = false;
    } else if (0 == strcmp("-c", args_list[i])) {
      file_list_parsing = true;
    } else {
      if (file_list_parsing) {
	files.push_back(string(args_list[i]));
      }
    }
  }
  if (files.size() == 0) {
    cerr << "-c must be specified with a list of files to check" << endl;
    return -1;
  }
  //---- End arugment handlers ----//

  Start_html(); //Start a new HTML output.

  for(uint i = 0; i < files.size(); i++)
    {
  ifstream fin(files[i].c_str());
  Dictionary dic(dictionary_file); //Dictionary file
  HashTable<int> incorrectWords; //Hash table for all incorrect words, explained below.
  Word_Count most_used; //Word counter for the most 'correct' words found during search
  Word_Count most_wrong;  //Word counter for the most commonly misspelled.

  //Ratio of misspelled to total words, incremented every time
  int totalCount = 0;
  

  //OUTPUT START HERE:

  Start_table(1, files[i]); //Begin HTML Formatting for spell check, files[i] is the filename.
  while(fin.good())
    {

      totalCount++; //New word has been counted.
      vector<string> s; //Reference vector for Dictionary::best_matches
      string word; 
      fin >> word; // word == next word in fstream


      for(unsigned int i = 0; i < word.length(); i++)
	{
	  word[i] = tolower(word[i]); //Convert to lowercase
	  if(!isalpha(word[i])) //Check for any non alpha characters
	    {
	       //If the word contains ', and ends in s, its assumed the word is possessive. Same goes for 't words.
	      if(word[i] == '\'' && ( word[i+1] == 's' || word[i+1] == 't') )
		{		
		  word.erase(i+1); //Remove the character after that apostrophe
		}
	      word.erase(i); //Remove the apostrophe
	    }
	}
      if (word.empty())
	continue;
      
      int *word_count;
      if ( (word_count = incorrectWords.Get(word)) ) {

	(*word_count)++;
	most_wrong.add_word(word);
	cerr << word << ":" << *word_count << endl;
      } 
      else if (!dic.best_matches(word, s, 3)) //If word doesn't exist in hash, and it's mispelled...
	{
	  most_wrong.add_word(word); //Add the word to most_wrong word count.
	  incorrectWords.Add(word, 1); //Add misspelled word to incorectWords
	  cerr << word << ":";      //Print the word
	  if (s.size() == 0) {
	    cerr << "No suggestions" << endl; // No possible suggestions found in tree.
	    continue;
	  }
	  for(unsigned int i = 0; i < s.size() - 1; i++) // Otherwise list all possible suggestions, comma separated.
	    {
	      cerr << s.at(i) << ",";
	    }
	  cerr << s.at(s.size() - 1) << endl;

	  //OUTPUT HERE(word, list);
	  Add_entry(word, s); //HTML Formatting using the incorrect word, and the vector<string> of all of it's suggestions.
	}

      most_used.add_word(word); //The word is spelled correctly, so add it to the most_used words.
    }

 End_table();


  //---- Vectors for total counts -----//
  vector<string> totalGoodWords;
  vector<int> totalGoodCounts;
  vector<string> totalBadWords;
  vector<int> totalBadCounts;

  //---- Write data to vectors ----//
  most_used.get_top_words(totalGoodWords, totalGoodCounts);
  most_wrong.get_top_words(totalBadWords, totalBadCounts);

  //---- Send data to HTML formatting ----//
  Start_table(2, "Most Common Words");
  for(int i = 0; i < n; i++)
    {
      Add_entry(totalGoodWords[i], totalGoodCounts[i]); //Overloaded HTML to take in Words, and Counts
    }

  End_table(); //End formatting

  Start_table(2, "Most Common Misspellings"); //Start new table for HTML
  for(int i = 0; i < n; i++)
    {
      Add_entry(totalBadWords[i], totalBadCounts[i]); 
    }
  End_table(); //End Formatting
  
  //---- Total Word Count ----//
  Start_table(2, "Total Word Count");
  Add_entry("Total: ", totalCount);
  End_table(); //End formatting
    }

  End_html();
  /* DEBUG */
  cerr << "Main() is returning 0\n";


  return 0;
}
//EOF
