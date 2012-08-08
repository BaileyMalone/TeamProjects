#include <string>
#include "Entry.H"

/* ***Entry Methods*** */
Entry::Entry(){}

/*
 * Overloaded Entry obejct constructor that provides a string value.
 */
Entry::Entry(string s)
{
  this->value = s;
  this->count = 1;
}

/*
 * Returns the number of times this Entry has been accessed/
 * found.
 */
int Entry::Count()
{ return this->count; }

/*
 * Returns the string value stored in the Entry object.
 */
string Entry::Value()
{ return this->value; }
/*
 * Returns true if the Entry objects have the same value;
 * false otherwise.
 */
bool Entry::Equals(Entry eo)
{
  if (this->Value().compare(eo.Value()) == 0)
    return true;

  return false;
}
/*
 * Returns the value of the Entry object.
 */
string Entry::ToString()
{
  return this->Value();
}
//EOF
