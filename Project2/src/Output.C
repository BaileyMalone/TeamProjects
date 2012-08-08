#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>

using namespace std;

// //Commented out due to makefile conflicts. Sorry.
// int main()
// {
//   return 0;
// }



//for printing the openening tags for the webpage.
void opening(string title, string header1, string header2, string img)
{
  cout << "<html><head><title>"
       << title 
       << "</title></head>"
       << "<body bgcolor = white align = center>"
       << "<img src ="
       << img
       << " align = center><br /><H1>"
       << header1 
       << "</H1><H1>"
       << header2 
       << "</H1><br />" 
       << endl;
}

//for printing the closing tags of the web page
void closing()
{
  cout << " <h3></h3></body></html>" << endl;
}


//for printing out the results of getting the top X words in a doc.
void To_html(vector<string> &word_list, vector<int> &counts)
{
  if(!word_list.size() == counts.size())
    { 
      cerr << "To_html: Vector size does not match" << endl;
      return;
    }
  stringstream ss;//make a string stream to build the header
  ss << "Top ";// add top the to header
  ss << word_list.size();//adding the int to the string.
  ss << " words in the document";// finnish the header.
  string number = ss.str();//assign the built string to the new variable.

  opening("Get top words results", number,"", "http://eng.utah.edu/~ccurtis/wrd_cnt.gif");
  cout << "<Table border = 1 width = 300 align = center bgcolor = lightblue>"
       << "<tr><th valign = top>word</th><th valign = top, width = 125>occurences</th></tr>" 
       << endl;// start the table
  for (uint i = 0; i < word_list.size(); i++)//fill the table
    {
      cout << "<tr><td>"
	   << word_list[i]
	   << "</td><td>"
	   << counts[i]
	   << "</td></tr>"
	   << endl;
    }
  cout << "</table>" << endl; // close the table.
  closing(); //close the page.
  
}
//for printing out the word count results of one word.
void To_html(string word, int count)
{
  opening("Word count result", "The word",
	  word, "http://eng.utah.edu/~ccurtis/wrd_cnt.gif");
  cout << "<H1>appears </H1><H1>"
       << count 
       << "</H1><H1> time(s) in the document</H1>"
       << endl;
  closing();
}

//for printing out the results of a spell check.
//this one is yet to be done.
void To_html(vector<string> &word_list, int percentage)
{
  string word, locations, options; // set these until args are figured out.
  word = "word_temp";
  locations = "1, 3, 4, 6";
  options = "option1, option2, option3";

  stringstream ss;//make a string stream.
  ss << percentage;//adding the int to the string.
  string strpercentage = ss.str();//assign the string to the new variable.
  opening("Spell Check results", "% of words spelled wrong:",
	   strpercentage, "http://eng.utah.edu/~ccurtis/spl_chk.gif");

  cout << "<table border = 1 width = 300 align = center bgcolor = 6c9c19>"
       << "<tr><th valign = top>misspelled word</th>"
       << "<th valign = top, width = 125>location in doc <br /> (word count)</th>"
       <<"<th valign = top>suggested corrections</th></tr>"
       << endl; //start the table

  for (uint i = 0; i < word_list.size(); i++)//fill the table
    {
      cout << "</tr><td>"
	   << word_list[i]
	   << "</td><td>"
	   << locations 
	   << "</td><td>"
	   << options
	   <<"</td></tr>"
	   << endl;
    }
      cout << "</table>" << endl; // close the table.
      closing(); //close the page.
}

void Start_to_html()
{
  opening("Spell Check results", "","Results", "http://eng.utah.edu/~ccurtis/spl_chk.gif");
  cout << "<table border = 1 width = 300 align = center bgcolor = 6c9c19>"
       << "<tr><th valign = top>misspelled word</th>"
    // << "<th valign = top, width = 125>location in doc <br /> (word count)</th>"
       <<"<th valign = top>suggested corrections</th></tr>"
       << endl;

}
void End_to_html()
{
  cout << "</table>" << endl; // close the table.
  closing();
}

void Add_to_html(string word, vector<string> &suggestions)
{
  //pull out suggested words into 1 string.
  stringstream ss;
  for (uint i = 0; i < suggestions.size(); i++)
    {
      ss << suggestions[i] << " ";
    }
  string suggested_words = ss.str();//assign the string to the new variable.

  cout << "<tr><td>"//add the word.
       << word
       << "</td>"
       << "<td>"
       << suggested_words
       <<"</td></tr>"
       << endl;
}

//** rework of methods to accomidate new specs.
//new version to start the html output.
void Start_html()
{
cout << "<html><head><title>"
     << "Team exception presents!" 
     << "</title></head>"
     << "<body bgcolor = white align = center>" << endl;
}

//new version to end html output.
void End_html()
{
  cout << " <h3></h3></body></html>" << endl;
}

//to start a table
void Start_table(int option, string message = "")
{
  string img; // the url of the image.
  string color; // the color of the table.
  string column1; // the name of the first column.
  string column2; // the name of the second column.


  if (option > 2 || option < 1 )
    {
      cerr << "invalid option used! " << option << endl;;
      return;
    }
  if (option == 1) 
    {
      img = "http://eng.utah.edu/~ccurtis/spl_chk.gif";
      color = "6c9c19";
      column1 =  "misspelled word";
      column2 = "suggested corrections";
    }
  if (option == 2)
    {
      img = "http://eng.utah.edu/~ccurtis/wrd_cnt.gif";
      color = "lightblue";
      column1 =  "word";
      column2 = "occurences";
    }

  cout << "<img src ="
       << img
       << " align = center><br /><H1>"
       << message 
       << "</H1><br />" 
       << "<table border = 1 width = 300 align = center bgcolor = "
       << color
       << "><tr><th valign = top>"
       << column1
       << "</th>"
       << "<th valign = top>"
       << column2
       << "</th></tr>"
       << endl;
}


//to add an entry in a started table.
void Add_entry(string word, vector<string> &suggestions)
{
  //pull out suggested words into 1 string.
  stringstream ss;
  for (uint i = 0; i < suggestions.size(); i++)
    {
      ss << suggestions[i] << " ";
    }
  string suggested_words = ss.str();//assign the string to the new variable.
  
  cout << "<tr><td>"//add the word.
       << word
       << "</td>"
       << "<td>"
       << suggested_words
       <<"</td></tr>"
       << endl;
}

//to add an entry in a started table.
void Add_entry(string word, int count)
{ 
  cout << "<tr><td>"//add the word.
       << word
       << "</td>"
       << "<td>"
       << count
       <<"</td></tr>"
       << endl;
}
//to end a table. the arg it takes in is 
void End_table(string message = "")
{
  cout << "</table><br/><h1>" 
       << message
       << "</h1><hr width = 80% noshade>"
       << endl; // close the table.
}

void test_output()
{
  vector<string> words; // make some variables for testing.
  words.push_back("word1");
  words.push_back("word2");
  words.push_back("word3");
  vector<int> counts;
  counts.push_back(1);
  counts.push_back(20);
  To_html(words, counts); // test the get_top_words output.
  To_html(words[0], counts[0]); // test the get_word_count output.
  To_html(words, 99); // and the last.

  //tests for second version
  Start_to_html();//test the spell_check_output functionality.
  Add_to_html("test_word", words);
  End_to_html();

  //tests for final versoin (hopefully)
  Start_html();
  Start_table(1, "test message");
  Add_entry("test_word", words);
  Add_entry("test_word", words);
  End_table("end message test");
  Start_table(2, "test message for word count");
  Add_entry("test_word", words);
  Add_entry("test_word", words);
  End_table("end message test word count");
  Start_table(4);// should cerr a message;
  Start_table(0);// should also print an error message;
  End_html();

}
