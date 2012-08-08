/*Credit to H. James de St. Germain for providing the code in parse_line
 *
 *Author(s): James Murdock and John Wells
 *Date: Spring 2012
 *
 */
#include <stdlib.h>

#include "Member.h"

using namespace std;

void Member::parse_line( string line )
{
  size_t start = 0;
  size_t end = line.find(" ", start);

  iGroupNumber = 0;               //set group to 0
  name = line.substr(start, end); //Name = the string contained within the start point and the first " "
  start = end+1;                  //Set position to the index after the first space.
  end = line.find(" ", start);    //Set end to the next space found
  skill = line.substr(start,end - start); 

  start = end + 1;                //Move to next position in line
  end = line.find(" ", start);

  string current_number;

  while (end != string::npos)
    {
      current_number = line.substr(start,end-start);

     
      availability[atoi ( current_number.c_str() )] = true;
      //Parse the current_number as an int, and use it as the index for availability, setting it to true.

      start = end+1;  //Increment start and end.
      end = line.find(" ", start);
    }
}
