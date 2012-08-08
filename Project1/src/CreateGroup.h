/*
 * CreateGroup.h
 * Author(s): John Wells and James Murdock
 * Date: Spring 2012 *
 *
 * Behavior: 
 * CreateGroup iterates through the Member 
 * array to match members with the same skill 
 * level into groups of 4.  If a member cannot 
 * be added to a group they will be assigned a 
 * groupid of 0, the 0 group represents members
 * that have no match for any other group due to 
 * time conflicts with remaining members left over 
 * for group selection.
 *
 */

#include <vector>
#include "Member.h"

using namespace std;
class CreateGroup
{
  public:
  CreateGroup(Member members[1000], int total);
  private:

};
