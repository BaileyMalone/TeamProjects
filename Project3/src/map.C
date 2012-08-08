/*
 * Map.H.C
 */

#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <list>
#include <sstream>
#include <ctype.h>
#include <ctime>
#include <curl/curl.h>
#include <iostream>

#include "map.H"
#include "Page.H"
#include "Word_Count.H"
#include "Dictionary.H"

using namespace std;

/*
 * <Team Exception> 
 * CS 3505 -- S12
 * Project 3: Web Crawler
 *
 *
 * Map is one of two functions in an architecture known as
 * "Map-Reduce". The idea is to take the original form of some 
 * data, and 'map' it into a more manageable form you then handle
 * with 'reduce'. 
 * Map is where our program uses threads primarily, and does all of
 * the CURLing actions.
 * Map CURLs source HTML and parses information accordingly.
 * 
 * RateLimiter is a handling class that ovverides the () operator to
 * provide throttle control for CURLing. The RateLimiter object with ()
 * makes a function call that has cross-thread awareness so that only
 * 8 threads per second may be running.
 *
 * NOTE: The significant majority of functions in map are just utility
 * functions for parsing, trimming or somehow adjusting strings.
 */

const char* user_agent = "cs3505_crawler";


/*
 * CURLs to a URL for a web page and stores the source HTML of that
 * page in the string "out source" which points to a locally managed
 * string object. 
 */
bool get_page(string url, RateLimiter &limit, string *out_source)
{
  cerr << "Curling this url: " << url << endl;
  limit();
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    //cerr << "Curl Object exists. Curling....\n" << endl;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, grab_HTML_src);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, out_source);
    //curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);

    // Get any ERRORS that might have been thrown and perform
    limit();
    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    

    return !res;
  }

  return false;
}

/*
 * <Original Source for Algorithm>:
 * helios on cplusplus.com @
 * www.cplusplus.com/forum/general/4422/
 *
 * Determines whether or not the parameter string is all 
 * digits or not.
 */
bool static HasText(std::string s)
{
  bool HasALetter = false;
  for (size_t i = 0; i < s.size(); i++)
    if (isalpha(s[i]) != 0){
      HasALetter = true;
    }

  return HasALetter;
}


/*
* <<Adapted from Proff. Germain's WriteFunction from lecture>>
*
* A "callback" curl write function to act when CURL has data
* available from its perform() start.
* Writes the source HTML to a string buffer variable so that
* a CURL page call can return all the HTML source from a page.
*/
size_t grab_HTML_src(void *ptr, size_t size, size_t n, void *data)
{
  ////printf("Grabbing-HTML-Src\n");

  // Reference Buffer
  std::string &pageInfo = *(std::string*)data;

  // Write the Page HTML to the buffer
  pageInfo.append((char*)ptr, size * n);

  return size * n;
}

/*
 * Finds the third '/', if it exists, in the parameter
 * string.
 */
int find_third_slash(std::string domain)
{
  size_t location = 0;
  int count = 0;
  while (count < 3)
    {
      location = domain.find("/", location+1);
      count += 1;
    }

  return location;
}

/*
 * Searches through and erases '/', '\', '>', '=', 'br' and
 * '<br' from the string parameter.
 * Although not a requirement, it is expected that the parameter
 * string represents a URL link.
 */
std::string WordTrim(std::string link)
{
  if (link.find("\"", 0) != std::string::npos){
    link.erase(link.find("\"", 0), 1);}

  if (link.find(">",0) != std::string::npos){
      link.erase(link.find(">",0));
  }
  if (link.find("/", 0) != std::string::npos){
    link.erase(link.find("\"", 0), 1);
  }
  if(link == "br" || link == "<br"){
    link.erase(0);
  }
  if (link[0] == '='){
    link.erase(0, 1);
  }


  return link;
}

/*
 * (Very similar to Wordtrim above, except both don't want
 * all of the same characters removed).
 */
std::string LinkTrim(std::string link)
{
  if (link.find("\"", 0) != std::string::npos){
    link.erase(link.find("\"", 0), 1);
  }
  if (link.find(">",0) != std::string::npos){
      link.erase(link.find(">",0));
  }
  if (link[0] == '='){
    link.erase(0, 1);
  }



  return link;
}


/*
 * Takes a relative URL and returns a complete version of
 * the URL using 'domain' as the domain name.
 */
std::string fix_path(std::string path, std::string domain)
{
  std::string full_link;

  std::stringstream ss;
  if (path[0] == '/')
    {
      string temp;
      int third_slash = find_third_slash(domain);
      domain = domain.substr(0, third_slash);
      ss << domain << path;
      full_link = ss.str();
    }
  else
    {
      string temp;
      size_t last_slash = domain.find_last_of('/');
      domain = domain.substr(0, last_slash+1);
      ss << domain << path;
      full_link = ss.str();
    }

    size_t amp = full_link.find("amp;", 0);

    while (amp != string::npos)
      {
	full_link.erase(amp, 4);

	amp = full_link.find("amp;", (amp+1));
      }

  return full_link;
}

/*
 * <<Adapted from Proff. Germain's code>>
 *
 * Runs amok amidst the HTML source string and creates a list
 * of all the href web links to a master list of links.
 */
void parse_links(std::string data, std::vector<std::string>* links, std::string url)
{
  //cerr << "Parse_Links URL = " << url << endl;
  //std::clock_t start = std::clock();
  //cerr << "Start parse_links..." << endl;

  /* Construct the list of links */
  //int found = data.find("href=\"http", 0);
  size_t found = data.find("<a href=\"", 0);

  // While there are still href_links in data 
  //size_t endLink = data.find("</", found);
  size_t openquote = data.find("\"", found);
  size_t closequote = data.find("\"", openquote+1);

  std::string href_str;
  std::string link;
  while (found != std::string::npos)
    {
      /* Trim the section for -just- the link */
      // Find the link(s)
      //href_str = data.substr(found, (endLink - found));
      //cerr << "href_str = " << href_str << endl;
      link = data.substr(openquote+1, (closequote - openquote)-1);
      // Cut to *just* the URL -- cut by ' " '
      // size_t first = href_str.find("\"", 0);
      // size_t last = href_str.find("\"", first+5);

      // link = href_str.substr(first+1, (last - first)-1);
      //if (link.find_last_of("\"",( link.size()/2)) != string::npos)
      //link.erase(link.find_last_of("\""));

      /* DEBUG */
      //printf("\nSRC --> %s\n", link.c_str());


      /* Relative or Absolute Path? */
      size_t check = link.find(":", 0);

      if (check != std::string::npos)
	{
	  links->push_back(link);
	  //printf("ABS_Link: %s\n\n", link.c_str());
	}
      else // is a Relative Path
	{
	  std::string newPath = fix_path(link, url);
	  links->push_back(newPath);
	  //printf("Fixed_Link: %s\n\n", newPath.c_str());
	}


      found = data.find("<a href=\"", closequote+1);
      openquote = data.find("\"", found);
      closequote = data.find("\"", openquote+1);
      
    }
  //cerr << "End parse_links  " << 
  //((std::clock() - start)/(double)CLOCKS_PER_SEC) << endl;
}

/*
 * Takes a string and removes any HTML related characters/
 * formatting from it.
 * (This string is likely from an HTML source doc).
 */ 
std::string stringize(std::string str)
{
  if (str[0] == '&'|| str[1] == '&'){
    str.erase();
  }
  else if ((str.find("()", 0) != std::string::npos) || 
	   (str.find(");", 0) != std::string::npos)){
    str.erase();
  }

  size_t x = str.find("<",0);
  size_t y = str.find(">",0);
  if (x != string::npos && y != string::npos)
    {
      ////printf("Erasing --> %s\n", str.substr(x, (y-x)+1).c_str());
      str.erase(x, (y-x)+1);
    }

  for (size_t i = 0; i < str.size(); i++)
      if ((str[i] == '>') || (str[i] == '<') || (str[i] == '\n') 
      || (str[i] == '\t') || (str[i] == '\r') || (str[i] == ',')
      || (str[i] == '&') || (str[i] == '"') || (str[i] == '!')
	  || (str[i] == '%') || (str[i] == '='))
	  str.erase(i, 1);

  /* DEBUG */
  //cerr << "End stringize  " <<
  //((std::clock() - start) / (double) CLOCKS_PER_SEC) << endl;

  return str;
}

/* 
 * Determines whether or not the parameter character is an ASCII 
 * punctuation character or not.
 */
bool IsPunctuation(char c)
{
  if ((c == '.') || (c == ':') || (c == ';') || (c == '-') || (c == ' ')
      || (c == '\n') || (c == '\r') || (c == '\t') || (c == '!')){
    return true;
  }
  return false;
}

/*
 * Designed similar, again, to WordTrim and LinkTrim, but meant to trim
 * leftovers from substring operations when parsing source HTML.
 */
std::string Trim(std::string str)
{
  for(size_t i = 0; i < str.size(); i++)
    {
      if ((str[i] == '>') || (str[i] == '"') 
	  || (str[i] == '\n') || (str[i] == '\t') || (str[i] == ',')
	  || (str[i] == '"') || (str[i] == '!'))
	{
	str.erase(i,1);
	}
    }
  
  return str;
}
/*
 * <Original Source> www.cplusplus.com
 * on "tolower"
 * Converts a string to all lower case.
 */
void static ToLower(std::string &str)
{
  std::string lowerStr;
  for(size_t i = 0; i < str.length(); i++)
      str[i] = tolower((str[i]));
}

/*
 * Splits the parameter string s into tokens as separated by
 * spaces or periods (std::string's are NOT null-terminated...).
 */
void tokenize(std::string s, Word_Count &words)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  //cerr << "Start tokenize..." << endl;

  int i = 0; int j = 0;
  
  string s2 = s + ".";  // Hack hack hack...

  std::string word;
  for (size_t x = 0; x < s2.size(); x++)
    {
      if (IsPunctuation(s2[x]))
	{
	  j = x;

	  word =  s2.substr(i, (j-i));

	  if (word.size() != 0)
	    {
	      for (size_t k = 0; k < word.size(); k++){
		if (word[k] == ' ')
		  {
		  word.erase(k, 1);
		  }
	      }
	      ToLower(word);
	      
	      if (word[0] == '/'){
		word.erase(0,1);}

	      if(!isdigit(word[0]))
		{
                  //cerr << "Adding word " << word << endl;
		  words.add_word(word);
		}
	    }

	  i = j+1;
	}
    }
  /* DEBUG */
  //cerr << "End tokenize  " <<
  //((std::clock() - start) / (double)CLOCKS_PER_SEC) << endl;
}

/*
 * Gets all English words on a source HTML page.
 * Words between '>' and '<' are expected to NOT be part of 
 * tags and therefore some form of English.
 */
void get_english(std::string data, Word_Count &english)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  //cerr << "Start get_english..." << endl;

  size_t c1 = data.find(">", 0);
  size_t c2 = data.find("<", c1);

  std::string sentence;
  while (c1 != std::string::npos && c2 != std::string::npos)
  {
    // Grab the english part
    sentence = data.substr(c1+1, (c2-c1)-1);

    //cerr << "Sentence: " << sentence << endl;
    if ((HasText(sentence)) & (sentence.find("{", 0) == std::string::npos) & 
	(sentence.find("jQuery", 0) == std::string::npos))
      {

	// Cut off any leftover carrots, and remove "&..." lines
	string temp = stringize(sentence);
	sentence = Trim(temp);

	/* DEBUG */
	//cerr << "Sentence: " << sentence << endl;

	// Tokenize the English part by whitespace
	if (sentence != "")
	  tokenize(sentence, english);

	//cerr << "English has " << english.NumberOfWords() << endl;
      }
    
    c1 = data.find(">", c2);
    c2 = data.find("<", c1);
  }
  /* DEBUG */
  //printf("End -- %i English words!  %i\n", 
  //english->NumberOfWords(),(std::clock() - start));
}

/*
 * For Amazon profile pages only -- gets the paragraph(s) of
 * English on a profile page, which is usually between a
 * "This review is from:" and a "</div>" tag.
 */
void get_review_english(std::string data, Word_Count &english, int &maxLength)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  //cerr << "Start get_review_english..." << endl;

  data.erase(0, 6);
  size_t c = data.find("This review is from:", 0);
  size_t d = data.find("</div>", c);
  if (d != std::string::npos)
    {
      string opinion = data.substr(d);

      std::string paragraphs;
      // Cut off any leftover carrots, and remove "&..." lines
      paragraphs = stringize(opinion);
      // Tokenize the English part by whitespace
      tokenize(paragraphs, english);

      // See if this review is the longest
      if (english.NumberOfWords() > maxLength)
	maxLength = english.NumberOfWords();
    }
  //printf("End -- Review has %i English words!  %i\n", 
  //english.NumberOfWords(), 
  //((std::clock() - start)/(double)CLOCKS_PER_SEC));
}

/*
 * Uses the referened Dictionary (from Project 2) to check the words
 * stored in the Word_Count object 'histogram'. 
 * Any misspellings are placed in 'misspelled'.
 *
 * NOTE: We are using the same Dictionary list as was provided by
 * Professor Germain for Project 2. As such, this list does *not*
 * include words such as "ipad" or "appstore" -- for a site like 
 * Amazon, this obviously introduces misspellings errors because
 * those words will be considered misspellings.
 */
void GetMisspellings(Word_Count *histogram, Word_Count *misspelled,
		     Dictionary &dic)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  //cerr << "Getting misspellings.." << endl;
  ////printf("**The Misspelled Words**\n");

  /* How do we iterate through a Word_Count object for the words? */
  std::vector<std::string> words = histogram->GetWords();

  for (size_t i = 0; i < words.size(); i++)
    {
      if (dic.spelled_correctly(words.at(i)) == 0)
	{
	  ////printf("misspelled! --> %s\n", words.at(i).c_str());
	  // *** Includes falsehoods! ipad, appstores, numbers....
	  misspelled->add_word(words.at(i));
	}
    }
  /* DEBUG */
  //cerr << "End get_misspelled  " << 
  //((std::clock() - start)/(double)CLOCKS_PER_SEC) << endl;
  // //printf("(end_misspelled_words)\n");
}

/*
 * INPUT: A review (cycle for each reviewer and check each
 *        review they make here.
 * OUTPUT: Number of spelling mistakes in this particular review.
 */
int number_of_misspellings(std::string review, int number, Dictionary &dic)
{
  Word_Count *words = 0;
  tokenize(review, *words);

  Word_Count *misspellings = 0;
  GetMisspellings(words, misspellings, dic);

  return misspellings->NumberOfWords();
}

/*
 * Takes the srouce HTML of an Amazon reviwer's profile page and 
 * substrings out the section that contains the review.
 * Every such text block is added to 'blocks'.
 */
void get_review_blocks(std::string data, std::vector<std::string> *blocks)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  //cerr << "Start get_review_blocks..." << endl;

  size_t bdry = data.find("<!-- BOUNDARY -->", 0);
  size_t end = data.find("other customers find the most helpful reviews", 0);
  std::string temp;
  while((bdry != std::string::npos) & (end != std::string::npos))
    {
      temp = data.substr(bdry, (end-bdry));
      blocks->push_back(temp);
      
      bdry = data.find("<!-- BOUNDARY -->", end);
      end = data.find("other customers find the most helpful reviews", bdry);
    }
  /* DEBUG */
  //cerr << "End get_review_blocks  " << 
  //((std::clock() - start)/(double)CLOCKS_PER_SEC) << endl;
}

/*
 * Takes the input string and finds the number in it.
 * It is expected that the string have only one number in it,
 * and the behavior otherwise is not clear.
 * Only send in strings as parameters that you believe have
 * only one number in them.
 */
int parse_number(std::string s)
{
  int x = 0;
  for (size_t i = 0; i < s.size(); i++)
      if (isdigit(s[i]))
	{
	  x = atoi(s.substr(i-1).c_str());
	}

  return x;
}

/*
 * Takes a string parameter 'section', which is the review block
 * for a review on Amazon. A review block includes the review text, 
 * and the associated HTML for that particular review.
 *
 * In the HTML lines are the price of the item and the star rating 
 * given by the reviewer -- these are pulled out and placed in
 * the vector of pair objects 'stars_cost'.
 */
void get_prices_and_stars(string section, 
			  std::vector< pair <double, double> >* stars_cost)
{
  pair<double, double> pair;

  // Price
  size_t dollarSign = section.find("$", 0);
  size_t alt = section.find("alt=", 0);

  string pr = ""; string star_str = "";
  if (dollarSign != string::npos && alt != string::npos)
    {
      // Grab the numbers
      size_t end_dollarSign = section.find("</", dollarSign);
      double price;
      if (end_dollarSign != string::npos)
	{
	  pr = section.substr(dollarSign, (end_dollarSign - dollarSign));
	  pr.erase(0,1);
	  price = atof(pr.c_str());
	}
      //printf("price = %f\n", price);

      // Grab the stars rating
      size_t rating = section.find(".", alt);
      size_t out = section.find("out", alt);
      double stars;
      if (rating != string::npos)
	{
	  star_str = section.substr(alt+5, (out - rating));
	  stars = atof(star_str.c_str());
	}
      //printf("stars = %f\n", stars);

      pair = make_pair(stars, price);
      stars_cost->push_back(pair);
    }
}

/*
 * Takes a vector of the English words contained in an Amazon review
 * and spellchecks them against the Project 2 dictionary reference
 * 'dic'.
 */
int get_reviewer_misspellings(vector<string> words, Dictionary &dic)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  //cerr << "Start get_reviewer_misspellings..." << endl;

  int misspellings = 0;
  std::vector<string>::iterator it;

  for (it = words.begin(); it < words.end(); ++it)
    if (!dic.spelled_correctly(*it)){
      misspellings += 1;}

  //printf("%i misspellings in this review.\n", misspellings);

  /* DEBUG */
  // cerr << "End get_reviewer_misspellings  " << 
  //((std::clock() - start)/(double)CLOCKS_PER_SEC) << endl;

  return misspellings; 
}

/*
 * Takes on page of a profile (some reviewers have enough reviews that 
 * they have multiple pages) and gets the information for a profile:
 * prices-stars, misspellings, total length of all reviews.
 */
void parse_profile(AmazonCustomer *customer, std::string profilePage, 
		   bool firstRun, Dictionary &dic, int &maxLength)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  //cerr << "Start parse_profile..." << endl;

  /* Total # of Reviews */
  if (firstRun)
    {
      size_t customerReviewsLine = profilePage.find("Customer Reviews</b>", 0);
      size_t endB_tag = profilePage.find("</b>", customerReviewsLine);
      size_t endDiv_tag = profilePage.find("</div>", endB_tag);

      if (customerReviewsLine != string::npos)
	{
	  // Number of Reviews
	  std::string temp_number = profilePage.substr(endB_tag, 
					      (endDiv_tag - endB_tag));
	  /* DEBUG */
	  ////printf("temp_number = %s\n", temp_number.c_str());
	  int numberOfReviews = parse_number(temp_number);
	  /* Set the Number of Reviews */
	  customer->number_of_reviews = numberOfReviews;
	}
    }
  /* *** GET THE BLOCKS FOR EACH REVIEW ON THIS PROFILE PAGE*** */
  // **? Go to the other pages 1.. to get ALL...?**
  size_t a = profilePage.find("<b>Availability:</b>", 0);
  size_t b = profilePage.find("<div style=\"padding-top:", 0);
  std::vector<string> single_reviews;
  while (a != string::npos && b != string::npos)
    {
      a = profilePage.find("<b>Availability:</b>", b);
      b = profilePage.find("<div style=\"padding-top:", a);

      if (a != string::npos && b != string::npos)
	{
	  string section = profilePage.substr(a, (b-a));
	  
	  /* DEBUG */
	  //cerr << "Getting review English..." << endl;

	  // Misspellings & + Avg Length of Reviews
	  // (length ~ text.NumberOfWords())
	  Word_Count text;
	  get_review_english(section, text, maxLength); // Words out of original order!
                                              // (hashing)

	  // -----------------------------------------------------------
	  
	  /* Individual reviews are gathered right about here .....*/
	  //	  //printf("text has %i English words!\n", text.NumberOfWords());


	  /* Set: Add to the total length of all reviews */
	  customer->length_of_reviews += text.NumberOfWords();
	  //printf("Number of Words in Reviews: %i\n\n", 
	  //customer->length_of_reviews);

	  /* DEBUG */
	  //cerr << "Getting Misspellings..." << endl;

	  int totalMisspellings = get_reviewer_misspellings
	    (text.GetWords(), dic);
	  customer->misspellings_count += totalMisspellings;


	  //cerr << totalMisspellings << " misspelings!" << endl;


	  /* DEBUG */
	  //cerr << "Getting Stars/Prices..." << endl;

	  /* Price(s) & Stars */
	  //(string section, map<pair <double, double> >* stars_cost);
	  get_prices_and_stars(section, &customer->stars_cost);
	}
    }


  /* DEBUG */
  cerr << "End parse_profile  " << endl;
  //((std::clock() - start)/(double)CLOCKS_PER_SEC) << endl;
}

/*
 * Every reviewer on Amazon has profile page on which you can see 
 * all of his or her reviews. Each page also sometimes has additional
 * pages on which the details of the other reviews are displayed.
 * This function takes the src for a profile page and finds if
 * such additional pages exist.
 * If any do, they are stored in the string vector "profileLinks".
 */
int how_many_more_profile_pages(string profilePage, 
				vector<string>* profileLinks)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  cerr << "Looking for additional profile pages for a user...\n" << endl;

  size_t pageOne = profilePage.find("Page: 1", 0);

  size_t href = string::npos;
  if (pageOne != string::npos)
    {
      href = profilePage.find("a href", pageOne);

      /* Separates multiples profile pages... ? */
      size_t BAR = profilePage.find("</a>", pageOne);

      while (href != string::npos)
	{
	  size_t EndOfPages = profilePage.find("</a></b>", BAR);

	  // if (href != string::npos)
	  //{
	      size_t quote = profilePage.find("\"", href);
	      size_t endLink = profilePage.find("\">", quote);
      
	      string domain("http://www.amazon.com/");
	      string rel_url = Trim(profilePage.substr(quote, (endLink-quote)));
	      string link = fix_path(rel_url,  domain);
      
	      if (link.find("page", 0) != string::npos)
		{
 		  //printf("***********************************\n");
		  //printf("rel_url --> %s\n\n", rel_url.c_str());
		  //printf("link --> %s\n", link.c_str());

		  /* Where/how do I return the number of other profiles? */
		  profileLinks->push_back(link);
		  //printf("***********************************\n\n");
		}

	      href = profilePage.find("a href", BAR);
	      // }
	  BAR = profilePage.find("</a>", href);

	  if (BAR > EndOfPages){
	    break;
	  }
	}
    }

  //cerr << "Done -- " << ((std::clock() - start)/(double)CLOCKS_PER_SEC) << endl;
    return 0;
}

/*
 * Takes a vector of review blocks for Amazon reviewers and
 * iterates through each one, grabbing the relevant data.
 * The reviewer's name, the link to his or her main profile 
 * page, and data specific to all of his or her reviews are
 * set up in Page and AmazonCustomer objects.
 * (This function especially makes liberal use of helper functions).
 */
void parse_reviewer_info(std::vector<AmazonCustomer> *customers, 
			 std::vector<std::string> *reviews, Dictionary &dic,
			  RateLimiter &limiter)
{
  /* DEBUG */
  //std::clock_t start = std::clock();
  cerr << "Start parse_reviewer_info..." << endl;

  //  int index = 0;
  std::string profilePage;

  std::vector<std::string>::iterator it;
  for (it = reviews->begin(); it != reviews->end(); ++it)
    {
      /* Grab the Name */
      size_t linkBefore = (*it).find("<a href", 0);

      size_t spanStart = (*it).find("<span", linkBefore);
      size_t endSpan = (*it).find("\">", spanStart);
      size_t beforeName = endSpan;
      size_t endName = (*it).find("</", beforeName);
      std::string temp = (*it).substr(beforeName, (endName-beforeName));
      std::string temp2 = stringize(temp);
      std::string name = Trim(temp2);

      // Set the Name
      AmazonCustomer customer(name);

      /* DEBUG */
      ////printf("Name Found - %s; Finding the rest...\n", name.c_str());

      /* Grab the profule url */
      size_t startLink = (*it).find("<a href", endName);
      size_t endLink = (*it).find("\">", startLink);
      std::string link = LinkTrim((*it).substr(startLink+7, 
					       (endLink-startLink)));
      std::string profile_link = Trim(link);
      
      /* DEBUG */
      ////printf("Base_Link --> %s\n\n", (*it).substr(startLink+7, 
      //(endLink-startLink)).c_str());

      /* DEBUG */
      ////printf("Curling profile...\n");
      //printf("Profile URL: %s\n\n", profile_link.c_str());


      /* ***Go to Profile and Grab: *** */
      // - Total Number of Reviews
      // - <double,double> of starts,price

      if (!get_page(profile_link, limiter, &profilePage)) {
        cerr << "Bad profile page curl at " << profile_link << endl;
      } else {
	  /* Parse the reviewer's profile */
	  //printf("Calling parse_profile...\n");
	int maxLength = 0;
	parse_profile(&customer, profilePage, true, dic, maxLength); 

	  /* More Pages on Profile Page? */
	  std::vector<std::string> profileLinks;
	  how_many_more_profile_pages(profilePage, &profileLinks);
	  
	  cerr << "Name: " << name << endl;
	  std::string profileSrc = "";
	  std::vector<std::string>::iterator it;
	  for (it = profileLinks.begin(); it < profileLinks.end(); ++it)
	    {
              if (!get_page((*it), limiter, &profileSrc)) {
                cerr << "Bad profile curl at " << (*it) << endl;
              } else {
                parse_profile(&customer, profileSrc, false, dic, maxLength);
              }
	    }
	  
	  customer.max_review_length = maxLength;

	  customers->push_back(customer);
	  profilePage = "";
	}

      // index += 1;
    }
  /* DEBUG */
  //cerr << "End parse_reviwer_info  " << 
  //((std::clock() - start)/(double)CLOCKS_PER_SEC) << endl;
}

/*
 * Checks the HTML source for a web page and increments 
 * this map run's Page object's count of images.
 */
void set_image_count(string data, Page *page)
{
  size_t img = data.find("<img", 0);
  //commented out to get rid of warnings.
  // size_t src = data.find("src=", img);

  while (img != string::npos)
    {
      //size_t end = data.find(">", src);
      // size_t isPng = data.substr(src, (end-src)).find(".png", 0);
      // size_t isJpg = data.substr(src, (end-src)).find(".jpg", 0);
      // size_t isBmp = data.substr(src, (end-src)).find(".bmp", 0);
      

      //if (isPng != string::npos || isJpg != string::npos || 
	  //  isBmp != string::npos){
	page->SetImageCount();
	//}
      size_t shift = img + 1;
      img = data.find("<img", shift);
    }
}

/*
 * --The Main Map Function-- 
 * Checks to make sure it is not crawling profile pages on Amazon
 * (this is something map was designed to do any time it finds
 * a reviewer).
 * Map determines whether we are on an Amazon or general web page,
 * as well as gathers general page data such as links and English.
 * If a page is found to be Amazon specific, other functions are
 * called to grab Amazon-related data.
 */
Page *Map(std::string url, RateLimiter &limiter, Dictionary &dic)
//Page Map(std::string url, Dictionary &dic)
{
  if (url.find("gp/pdp/profile", 0) == string::npos)
    {
      ////printf("DOING REAL CURL WORK\n");
      cerr <<"Curling this URL: " << url << endl;
      Page *page = new Page(url);

      //string filename ("words.txt");
      //Dictionary dic(filename);
      /* DEBUG */
      //printf("Dictionary has %i words\n", dic.Size());

      /* CURL */
      std::string pageInfo;
      Word_Count *wordHistogram = new Word_Count();
      Word_Count *misspelled = new Word_Count();
      std::vector<std::string> listOfLinks; 
      
      if (!get_page(url, limiter, &pageInfo)) {
        cerr << "Bad curl on " << url << endl;
        return 0;
      }


	  // *** <Set Up page Object!> ***
	  // <Set Up List_of_Links>
	  parse_links(pageInfo, &listOfLinks, url); // GET all Href-Links
	  //cerr << "List of links size: " << listOfLinks.size() << endl;
	  page->SetLinks(listOfLinks); 

	  /* DEBUG */
	  //printf("List-of-Links is %lu strong!\n", listOfLinks.size());

	  get_english(pageInfo, *wordHistogram); // GET all words and counts

	  /* DEBUG */
	  //cerr << "Found " << (*wordHistogram).NumberOfWords() << 
	  //" words." << endl;

	  GetMisspellings(wordHistogram, misspelled, dic);

	  // Number of Images
	  set_image_count(pageInfo, page);


	  // <Set Up Word Histogram>
	  page->SetHistogram(wordHistogram);  
	  page->SetBadWords(misspelled);

	  /* Amazon Specific Stuff */
	  if (url.find("amazon.com") != std::string::npos)
	    {
	      page->isAmazonPage = true;

	      /* DEBUG */
	      //printf("On an Amazon Page!\n");

	      // Vector of Review_Src_Blocks
	      // The 'string interval' [BOUNDARY, 
	      //                     "Help other customers find the most helpful
	      //                      reviews"]
	      std::vector<std::string> reviewBlocks;

	      //printf("Getting Review blocks...\n");

	      get_review_blocks(pageInfo, &reviewBlocks); 

	      /* DEBUG */
	      //printf("%lu Review Blocks Found.\n\n", reviewBlocks.size());
	      //printf("Parsing_Reviewer_Info...\n");

	      //vector<string> reviewers;
	      std::vector<AmazonCustomer> reviewers;
	      parse_reviewer_info(&reviewers, &reviewBlocks, dic, limiter); 
	      page->SetReviewers(reviewers);
	      /* DEBUG */
	      //printf("Setting_Reviews_in_Page\n");
	    }
	  //cerr << "****\nreturning page -- " << page->GetLinks().size() 
	  //<< " links\n****" << endl;
      return page;
    }

  return 0;
}
