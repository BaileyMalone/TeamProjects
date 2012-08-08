#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>


# include <sys/types.h> //to make this compile on my mac

#include "Output.H"

using namespace std;

void example_out()
{
  Output o;
 vector<string> headers;//make some stuff to give the methods.
  headers.push_back("pages visited");
  headers.push_back("ave words/image");
  headers.push_back("ave links/image");
  headers.push_back("ave misspellings/page");

  //test start html()
  o.start_html(true);

  //test start_table() with option3 for the web crawler
  o.start_table(3, headers, "results of crawling yo mamma");

  //test add_entry() add the entries for web crawler
  vector<int> cells;//make some stuff to give the methods.
  cells.push_back(5);
  cells.push_back(1000);
  cells.push_back(10);
  cells.push_back(24);
  
  for (uint i = 0; i < cells.size(); i++)
    {
      o.add_entry(cells[i]);
    }
  
  o.end_table();//end the web crawlers table

  headers.clear();
  headers.push_back("ave star/customer");
  headers.push_back("ave lenght of review");
  headers.push_back("ave misspellings/review");

 //test start_table() with option4 for the amazon extras table
  o.start_table(4, headers, "stats specific to amazon.com");
 
 //add the entries for amazon
  for (uint i = 0; i < headers.size(); i++)
    {
      o.add_entry(cells[i]);
    }
  o.add_entry("more tests");
  o.add_entry(40000000); //test adding a large int to see if it outputs scientific notation
  o.add_entry(400/400000);//test adding a small double.
  cerr << "actual value of 400/400000: " << 400/400000 << endl;
  o.add_entry((double)40000000); //test adding a large int to see if it outputs scientific notation
  o.add_entry((double)(400/400000));//test adding a small double.
  cerr << "actual value of 400/400000: " << (double)( 400/400000) << endl;
  //end amazon extras table
  o.end_table();

  headers.clear();
  headers.push_back("word");
  headers.push_back("count");
  headers.push_back("word");
  headers.push_back("count");
  headers.push_back("word");
  headers.push_back("count");
  
 //test start_table() with option1 for the most misspelled words
  o.start_table(1, headers, "top 100 mispelled words");
  for (uint i = 0; i < 100; i++)
    {
      o.add_entry("testword");
      o.add_entry((int)i);
    }
  //end top misspelled words table
  o.end_table();


 //test start_table() with option2 for all words counted
  o.start_table(2, headers, "total words found");
  for (uint i = 0; i < 300; i++)
    {
      o.add_entry("test");
      o.add_entry((int)i);
    }
  o.end_table();//end total word count table.

}
int main()
{
  Output out;

  //out.test();
  example_out();
  return 0;
}
