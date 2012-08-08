/*
 * page.C
 */

#include <vector>
#include <string>
#include "Page.H"

using namespace std;

void Page::SetLinks(vector<string> links)
{
  this->list_of_links = links;
}

void Page::SetBadWords(Word_Count *misspellings)
{
  this->BadWords = misspellings;
}

void Page::SetHistogram(Word_Count *histogram)
{
  this->Histogram = histogram;
}

void Page::SetReviewers(vector<AmazonCustomer> revs)
{ this->reviewers = revs; }

void Page::SetImageCount(){
  image_counter++;
}

vector<string> Page::GetLinks()
{ return this->list_of_links; }

string Page::Url()
{ return this->url; }

// Returns the histogram of words
Word_Count *Page::GetHistogram()
{ return this->Histogram; }

// Returns the number of misspellings (on a page)
Word_Count *Page::GetMisspellings()
{ return this->BadWords; }

// Returns the reviewers list for an Amazon page
std::vector<AmazonCustomer> Page::GetReviewers()
{ return this->reviewers; }

int Page::GetImageCount()
{ return this->image_counter; }

Page::~Page() {
  delete BadWords;
  BadWords = 0;
  delete Histogram;
  Histogram = 0;
}
