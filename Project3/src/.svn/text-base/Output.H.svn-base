/*
 * Output.H
 * Team: Exception
 * Date: Spring 2012
 * version 2.0 changed funtions to a class
 *
 */

#ifndef _OUTPUT_H
#define _OUTPUT_H

#include <string>
#include <vector>

class Output
{
public:
  /**
   *a consructor... yeah it does nothing.
   */
  Output(){}

  /*a method to start building an html output. The optional arg
   *is to set if output will cout on the fly or save it up as a
   *big string and ouput it at the end of the page.
   *true will result in printing on the fly
   *false will save it up and print on a end_html() call only
   */ 
  void start_html(bool print_or_collect);
 
  /*a method to start outputting a table in html.
   *the arg option is to determine the image and table color as follows:
   *0 = no image, light gray table
   *1 = spell check image, green table
   *2 = word count image, blue table
   *3 = web crawler image, gray table
   *4 = amazon extra image, orange table
   *&column_headers is a vector of strings that will become the headers
   *   of the columns and its length determines the width of the table.
   *string message is an optional arg for puttinng text above the table.
   */ 
  void start_table(int option, std::vector <std::string> &column_headers, std::string message = "");
  
  /*a method to add a single entry to the table
   *it is overloaded many times to accept many differing args such as;
   *string entry
   *int entry
   *vector<int> &entry
   *vector<string> &entry
   *caution* when reaching the end of a row in the table these methods
   *         will continue on to the next row on the next call. This
   *         could lead to unexpected ouputs if not careful.
   *more overloads may be added if needed.
   */
  void add_entry(std::string entry);
  void add_entry(std::vector<std::string> &entry);
  void add_entry(int entry);
  void add_entry(std::vector<int> &entry);
  void add_entry(double entry);

  /*a method to end a table. this will close the table and reset the table 
   *options and add a divider to the page. It will also finnish off the table
   *if all the cells in the row are not filled.
   *the optional are is if you want a message below the table
   */
  void end_table(std::string message = "");

  /*a method to end the html output and cout the whole thing or just
   *the ending tags depending on what arg was passed to start_html.
   */
  void end_html();

  //makes the ouput object run it's unit tests.
  void test();
};


#endif /* _OUTPUT_H_ */
