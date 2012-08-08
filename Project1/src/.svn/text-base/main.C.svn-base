/*
 *Credit to H. James de St. Germain for providing a faster method to parse a file. 
 *Authors: John Wells and James Murdock
 *Source(s): Example code provided by H. James De St. Germain
 *Date: January 20th, 2011
 *
 */
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>

#include "CreateGroup.h"

using namespace std;

int
main(int arg_count, char *arg_list[])
{
  FILE *file;
    if(arg_count == 1)
      {
	file = fopen("realworld_data.txt","r"); //Default file to read if none supplied
      }
    else 
      {
	file = fopen(arg_list[1], "r"); //Read the first command arg as a file.
      }
  if (!file)
    {
      printf("Error\n");
    }
  Member members[1000]; //Maximum feasible number of students in a class
  char line[1000];      //Maximum feasible number of characters per line.
  int count = 0;

  while( fgets( line, 1000, file) && count < 1000) //Read every line of the file
    {
      members[count].parse_line( line ); //Parse the line informaton as a Member Object
      count++;
    }

  //Call creategroup here, using the array of members created above.
  CreateGroup(members, count - 1);
  //cout << "Complete" << endl;
  return 0;
}
