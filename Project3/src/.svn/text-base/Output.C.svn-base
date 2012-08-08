#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <sys/types.h>

#include "Output.H"

using namespace std;

char nl = '\n';
int table_width;
int current_column;
string accumulator;
string image;
string style;
string color;
bool print = false;

void print_or_build()
{
  if (print)//if print is true cout the accumulator and reset the accumulator.
  {
    cout << accumulator << endl;
    accumulator.clear();
  }
  //otherwise keep building the string.
}

string int2string(uint number)
{

//   string str;
//   return itoa(number,str, 10 );
 stringstream ss;
  ss << number;
  return ss.str();//assign the string to the new variable.
}

string dbl2string(double number)
{
  //think fixed.. fixes the scientific notation problem.
  stringstream ss;
  ss << setprecision(4) << fixed << number;//set the precision we want the double to be.
  return ss.str();//assign the string to the new variable.
}

void set_options(int option)
{
switch (option) {
 case 0://no image light blue tables
   image = "";
   color  = "lightgrey";
   break;
 case 1://spell check image and green tables
   image = "<img class='displayed' src = 'http://eng.utah.edu/~ccurtis/spl_chk.gif' align = 'center'>";
   color  = "6c9c19";
   break;
 case 2://word count image and blue tables
   image = "<img src = http://eng.utah.edu/~ccurtis/wrd_cnt.gif align = center>";
   color  = "lightblue";
   break;
 case 3://crawler image and gray tables
   image = "<img src = http://eng.utah.edu/~ccurtis/web_crawl.gif align = center>";
   color = "gray";
   break;
 case 4://amazon extras
   image = "<img src = http://eng.utah.edu/~ccurtis/amazon.gif align = center>";
   color = "F69404";
   break;
 default:
    cerr  << "invalid start_table option: " << option << endl;
  }

}


void Output::start_html(bool print_or_collect = true)
{ 

  style =  (style + "<style type = 'text/css'>"
	    +"body {background-color:#FFFFFF; text-align:center }"
	    +"IMG.displayed {display: block;margin-left: auto;margin-right: auto}"
	    +"th,td {text-align:center}"
	    +"</style>");//set up some style info

  print = print_or_collect;//set the print or build var.
  //starting tags for a webpage
  accumulator = (accumulator + "<html><head><title> Team exception presents!</title>"
		 + style
		 +"</head><body align = center>");
  accumulator += nl;//add a new line for html readability.
  print_or_build();//either print to cout or keep building string.
}

void Output::start_table(int option, 
		 vector <string> &column_headers, 
		 string message) 
{
  table_width = column_headers.size();//set the width of the new column.
  set_options(option);//set the table options
  accumulator += (image 
		  + "<br /><H1>"
		  + message
		  + "</H1><br />"
		  + "<table border = 1 align = center bgcolor = "
		  + color
		  + "><tr>");//add the tags to start the table.

  accumulator += nl;//add newline char for html readability

  while (current_column < table_width)//put in the headers for the table
    {
      string header = column_headers[current_column];
      accumulator += ("<th WIDTH = '"
		      + int2string(header.length() + 4)
		      + "0'>"
		      + header
		      + "</th>");
      current_column ++;
    }
  accumulator += "</tr>";//end the row
  accumulator += nl;//add a new line for html readablity.
  current_column = 0;//make sure the current_column is reset.
  print_or_build();//either cout results or keep building.
  return;
}

void Output::add_entry (string entry)
{
  if(current_column == 0) //if the current column is 0 then start a new row
    {
      accumulator += ("<tr><td>" + entry + "</td>");// add entry in new row
      current_column ++;//increment the column.
      return;
    }
  if (current_column == (table_width - 1))// if the current column is the last one.
    {
      accumulator += ("<td>" + entry + "</td></tr>");//add the entry
      accumulator += nl; //add the newline character for html readbility
      current_column = 0;//set column for the new row
      return;
    }
  else // the cell is a column somewhere in the middle
    {
      accumulator += ("<td>" + entry + "</td>");// add the entry.
      current_column ++;// set to the next column.
    }
  print_or_build();// keep building the string or cout?
  return;
}

void Output::add_entry (int entry)
{
  add_entry(int2string(entry));
  print_or_build();
}

void Output::add_entry (double entry)
{
  add_entry(dbl2string(entry));
  print_or_build();
}

void Output::add_entry (vector <int> &entry)
{
  string collector = "";//set up a collector to get all the strings
  for (size_t i = 0; i < entry.size(); i++)  //collect all the ints
    {
      collector += int2string(entry[i]);//convert the int and it to the collector.
      collector += ", ";
    }
  collector.erase(collector.length() - 2); //remove the last comma to make it pretty.
  add_entry(collector);// add the entry to the table
  print_or_build();
}

void Output::add_entry (vector <string> &entry)
{
  string collector = "";//set up a collector to get all the strings
  for (size_t i = 0; i < entry.size(); i++)  //collect all the strings in entry into 1 string
    {
      collector += entry[i];
      collector += ", ";
    }
  collector.erase(collector.length() - 2); //remove the last comma to make it pretty.
  add_entry(collector);// add the entry to the table
  print_or_build();
}

void Output::end_table(string message)
{
  // check to see entries are in the middle of the row if it is
  // finnish off the row.
  if (current_column > 0)
    {
      while (current_column < table_width)
	{
	  accumulator += ("<td>&nbsp </td>");//add tags to finish row of table
	  current_column ++;//increment the position.
	}
      accumulator += "</tr>";//end the row.
    }
  accumulator += nl;
  //close the table and put in a divider, maybe a message.
  accumulator += ("</table><br/><h1>" 
		  + message 
		  + "</h1><hr width = 80% noshade>");
  accumulator += nl;//add the newline for html readability.
  print_or_build();
  table_width = 0;//reset the table vars
  current_column = 0;
  return;
}

void Output::end_html()
{
  accumulator += ("<h3></h3></body></html>");//add the tags to end the page
  accumulator += nl;//add the newline for html readability.
  print = true;//set this variable to ensure a cout
  print_or_build();//print what has accumulated.
}

void Output::test()
{
 //set up for tests
  vector<string> headers;//make some stuff to give the methods.
  for (size_t i = 0; i < 5; i++)
    {
      headers.push_back("words");
    }

  //test start html()
  cerr << "the results of start_html() test: " << endl;
  start_html(true);

  //test start_table() with option1
  cerr << "the results of start_table test with option1: " << endl;
  start_table(1, headers, "testing start_table option1: ");

  //table width should be 5
  //current column should be 0
  cerr << " table size passes: " << (table_width == 5) << endl;
  cerr << " current column passes: " << (current_column == 0) << endl;

  //test add_entry()
  cerr << "the results of add_entry(string) test: " << endl;
  
  for (size_t i = 0; i < headers.size(); i++)
    {
      add_entry(headers[i] + "entry");
    }

  cerr << "after adding 1 more entry: " << endl;
  add_entry("one more entry");

  //table width should still be 5
  //current column should be 1
  cerr << " table size passes: " << (table_width == 5) << endl;
  cerr << " current column passes: " << (current_column == 1) << endl;

  cerr << "the results of end_table(message) test: " << endl;
  end_table("testing the end table");
  
  //table width should still be 0
  //current column should be 0
  cerr << " table size passes: " << (table_width == 0) << endl;
  cerr << " current column passes: " << (current_column == 0) << endl;

 //test start_table() with option2
  cerr << "the results of start_table test with option2: " << endl;
  headers.clear();
  headers.push_back("head1");
  headers.push_back("crap");
  start_table(2, headers, "testing start_table option2: ");

  //table width should be 2
  //current column should be 0
  cerr << " table size passes: " << (table_width == 2) << endl;
  cerr << " current column passes: " << (current_column == 0) << endl;

  //test add_entry()
  cerr << "the results of add_entry(string) test: " << endl;
  add_entry("an entry");

  //table width should still be 2
  //current column should be 1
  cerr << " table size passes: " << (table_width == 2) << endl;
  cerr << " current column passes: " << (current_column == 1) << endl;

  end_table("testing the end table");

 //test start_table() with option 3
  cerr << "the results of start_table test option 3: " << endl;
  headers.clear();
  headers.push_back("head1");
  headers.push_back("crap");
  start_table(3, headers, "testing start_table option3: ");

  end_table("testing the end table");

 //test start_table() with option 4
  cerr << "the results of start_table test option 4: " << endl;
  headers.clear();
  headers.push_back("head1");
  headers.push_back("crap");
  start_table(4, headers, "testing start_table option4: ");

  end_table("testing the end table");

 //test start_table() with option 0
  cerr << "the results of start_table test option 0: " << endl;
  headers.clear();
  headers.push_back("head1");
  headers.push_back("crap");
  start_table(0, headers, "testing start_table option0: ");

  //add and entry that will have a vector of words in 1 cell.
  cerr << "add a one cell entry with multiple words to test overload." << endl;
  headers.push_back ("entry3");
  add_entry(headers);

  //test the add_entry(int) overload.
  cerr << "testing add_entry(int)" << endl;
  add_entry(50);
  add_entry(100);

  //test the add_entry(double) overload.
 cerr << "testing add_entry(double)" << endl;
  double d;
  d = 50/3.7;
  add_entry(d);
  vector<int> numbers;
  numbers.push_back(5);
  numbers.push_back(4);
  numbers.push_back(3);
  numbers.push_back(2);
  //test the add_entry(vector<int>)overload
  add_entry(numbers);
  end_table("testing the end table");

  cerr << "the results of end_html() test: " << endl;
  end_html();
  
  //table width should still be 0
  //current column should be 0
  //accumulator should be "".
  cerr << " table size passes: " << (table_width == 0) << endl;
  cerr << " current column passes: " << (current_column == 0) << endl;
  cerr << " acumulator passes: " << (accumulator == "") << endl;
//test 
}
