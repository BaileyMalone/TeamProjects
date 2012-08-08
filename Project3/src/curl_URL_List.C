#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <curl/curl.h>

using namespace std;


/* TO-DO */
/*
 *Determine and Implement:
 * (1) threshold for searching through pages,
 * (2) looping condition/mechanism (threshold dependent),
 * (3) What I'm looking for / what to do with the data on
 *     the pages I'm searching through.
 */



/**
 * Called by libcurl to download/handle each part of
 * the webpage as it comes in.
 *
 * Parameters:
 * - ptr --> a void pointer (~null-terminated string)
 * - size --> how many lines of data
 * - nmemb --> how many bytes in line
 * - userdata --> a void pointer (to a string)
 *
 */
size_t write_function(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  // Reference Buffer
  /* This exact variable is defined in main PRIOR to setopt w_f! */
  /* ==> Can pull data back out in program after file transfer */
  string &buffer = *(string*)userdata;

  /* DEBUG */
  printf("In Write_Function: size %d, nmemb %d, userdata %p\n", size, 
	 nmemb, userdata);

  // "Save state" ?
  buffer.append((char*)ptr, size * nmemb);

  return size * nmemb;
}

/**
 * A simple HTML parsing function.
 * Finds and prints "href"s and prints them.
 *
 * data ~ a string of a web page's >>ENTIRE<< HTML source
 */
void parse_html(string data, vector<string>* urls)
{
  int found = data.find("href=\"http", 0);

  /* WHILE there are still href_links in data */
  int endLink = data.find("</", found);
  while (found != string::npos)
    {
      // Find the link(s)
      string href_str = data.substr(found, (endLink - found)); 
      //printf("$$$$$:  %s\n", href_str.c_str()); 
      // Cut to *just* the URL
      int last = href_str.find("\">", 0);
      int first = href_str.find("ht", 0);
      //printf("URL = %s\n", href_str.substr(first, last).c_str());

      urls->push_back(href_str.substr(first, (last-first)));

      //printf("(found, endLink) = (%d, %d)\n\n", found, endLink);

      found = data.find("href=\"http", found+10);
      endLink = data.find("</", found);
    }
}


void static TrimVector(vector<string>* v)
{
  for (int i = 0; i < (*v).size(); i++)
    if ((*v)[i] == "")
      v->erase(v->begin()+i);
}

/**
 * Test program for CURL.
 * Open page --> read page source --> print all hrefs.
 */
int main()
{
  CURL *curl;
  CURLcode res;
  string buffer;

  vector<string> urls;

  /* TO-DO */
  // Threshold?
  // Looping condition?
  // Storage?

  curl = curl_easy_init();

  /* Put the below into a function that takes an argument s.t. */
  /* argument ~ web address for new page */

  // Initialize the behavior of curl
  if (curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL, "http://www.utah.edu");
      /* Use this on Each-New-Page until **depth_threshhold** */
      //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

      // Behavior set -- Call CURL.Perform()
      res = curl_easy_perform(curl);

      /* Check if any errors were thrown! */
      if (res)
	printf("Error! Res is %d\n", res);


      // Cleanup
      curl_easy_cleanup(curl);
    }

  /* Data Gathered --> Parse the data! */
  parse_html(buffer, &urls);

  TrimVector(&urls);

  /* Verify the Vector-of-URLs method */
  for (int i = 0; i < urls.size(); i++)
    cout << "v:  " << urls[i] << endl;




  return 0;
}
