/*
 * Output.H
 * Team: Exception
 * Date: Spring 2012
 *
 */

#ifndef _OUTPUT_H
#define _OUTPUT_H

//a function to test the various output functions
void test_output();
//take in a vector of word refs and a vector of counts refs and outputs 
//to html text the top occuring words in the doc.
//for outputing the results of get_top_words()
void To_html(vector<string> &word_list, vector<int> &counts);

//takes in a string and an int (suposedly from get_word_count()) and 
//couts the results to html formatted texts.
//for outputting the results of get_word_count().
void To_html(string word, int count);

//what this overload takes in is TBD could be any number of things from the
//dictionary class.
//idealy something like To_html(vector<string> &word_list, 
//for outputting the sumarry of spell checking the document.
void To_html(vector<string> &word_list, int percentage);

// to start an output webpage for spell check. produces the title headers and starts the table.
void Start_to_html();

// to end an output webpage for spell check. adds tags to close the table and page.
void End_to_html();

// to add a word entry to the html table.
void Add_to_html(string word, vector<string> &suggestions);


//** rework of methods to accomidate new specs.
//new version to start the html output. just the opening tags for the page.
//for page to be complete End_html() should follow this when all the outputs are finnished.
void Start_html();

//new version to end html output. just the closing tags for a page
void End_html();

//to start a table message is an optional arg if one wants to add a message to the top of the table.
// EX: "for file "X" these are the top mispelled words."
//option is an in to determing if this will be a spellcheck table or a word count table. image will
// be determined by this number. 1 for spell check 2 for word count.
// table will have two columns. for spell check, titled "misspelled" word and "suggestions"
//for word count title "word" and "occurances"
//for page to be complete End_table should follow this when finnished.
void Start_table(int option, string message = "");


//to add an entry in a started table.
//all entries will result in a two cell row in a started table.
void Add_entry(string word, vector<string> &suggestions);

//overloaded for outputting word count.
void Add_entry(string word, int count);

//to end a table. message is an optional arg if one wants to add a message at the bottom of the table.
void End_table(string message = "");


#endif /* _OUTPUT_H_ */
//EOF
