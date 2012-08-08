/**
 * CreateGroup.C
 * Author(s): John Wells and James Murdock
 * Date: Spring 2012
 *
 */
#include <iostream>
#include <stdio.h>
#include "CreateGroup.h"


using namespace std;

CreateGroup::CreateGroup(Member members[1000], int count)
{
  int index = 0; //Used for keeping track of current group 'leader' when assigning new members.
  int groupCount = 1; //Group counter, increments whenever a team member is matched.
  int groupID = 1; //Group ID counter, keeps track of the groups the members are placed into.
  int hourCount; //Counter for hours in the member's schedule. For every match, hour++
  bool groupAvailability[168]; //Array to house the AND values of all group members. Prevents one user from being added with schedule conflicts.
  

  for(int i = 0; i <=count; i++) //From 0 to the end of the list of students
    {
      
      //If current member is NOT grouped,
      if(members[i].iGroupNumber == 0)    //selects the group leader
	{
	  for(int j = 0; j < 168; j++)
	    {
	      //Sets the group availability to reflect that of the 'leader'
	      groupAvailability[j] = members[i].availability[j]; 
	    }

	  groupCount = 1;
	  index = i; //Set Current student's position as the index
	}
     else
       continue; //If student is grouped already, proceed to next iteration.

      for(int i = index + 1; i <= count; i++) //Take the student AFTER the previosly selected student.
	   {

	     hourCount = 0;

	     //If the member isn't grouped, the group contains less than 4 members, and the member's skill is equal to the group...
	     if((members[i].iGroupNumber == 0) && groupCount < 4 && (members[i].skill.compare(members[index].skill) == 0))
	       {
		 for(int j = 0; j < 168; j++)
		   {
		     //For every hour of availability shared, increment by one
		     if(groupAvailability[j] == members[i].availability[j])
		       {
			 
			 hourCount++;
			 
			 //If member can meet at least 5 hours per week, add member to current group.
			 if(hourCount == 5)
  			   {

			     members[i].iGroupNumber = groupID; //Reflect that the member has been grouped.
			     groupCount++; 
			     // If there are four members in the group
			     if(groupCount == 4)
			       {
				 members[index].iGroupNumber = groupID; //Set the index member's group id, this prevents grouping problems
				 groupID++;
				 break;
			       }

			     for(int k = 0; k < 168; k++)
			       {
				 //set group availability to reflect the new members hours (using AND)
                                 groupAvailability[k] = members[index].availability[k] && members[i].availability[k]; 
                               }
			        		     
				
			   }
		       }
		   }

	       }
	     
	      
	   }

	 //Set index back to 0, and start again.
      // index = 0;
    
}
  printf("<html>\n"
	 "<head>\n"
	 "</head>\n"
	 "<body>\n"
	 "<table border = \"1\">\n"
	 "<tr>\n"
	 " <th>Student:</th>\n"
	 "<th>Skill Level:</th>\n"
	 "<th>Group Number:</th>\n"
	 "</tr>\n");

  for(int m = 0; m <= groupID; m++)
    {
  //Output the results.
      //cout << "----------" <<endl;  
    for(int ii = 0; ii <= count; ii++)
      {
      if(members[ii].iGroupNumber == m)
      printf("<tr><td>%s</td><td>%s</td><td>%i</td></tr>\n", members[ii].name.c_str(), members[ii].skill.c_str(), members[ii].iGroupNumber);
      //cout << members[i].name << " " << members[i].iGroupNumber << endl;
      }
    }  
  printf("</table>"
	 "</body>"
	 "</html>");
}
