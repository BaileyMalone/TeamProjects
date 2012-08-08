#include <string>
#include <iostream>
#include <sstream>
#include "HashTable.H"
using namespace std;

/*
 * Author: Bailey Malone
 * Team Exception
 * Purpoose: CS 3505, S12
 */


void static AddTest1(string s, int i)
{
  cout << "--AddTest1--\n";
  cout << "Trying to add " << "(" << s << "," << i << ")\n";

  HashTable<int> table;
  table.SetSize(10);

  // Add s to the table
  table.Add(s, i);

  // Print out the table and make sure t is there
  int p = *table.Get(s);
  cout << "Get entry back: " << p << "\n";
}

// Tests the map functionality -- counting duplicate additions?
void static AddTest2(string s, int i)
{
  cout << "--AddTest2--\n";
  cout << "Adding (" << s << "," << i << ")" << " twice gives a count of:\n";

  HashTable<int> table;
  table.SetSize(10);

  table.Add(s, i);
  table.Add(s, i);

  // Print out the count for s -- it should be 2!!
  cout << *table.Get(s) << "\n";
}

void static AddTest3(string s, int i)
{
  cout << "--AddTest3--\n";
  cout << "Adding (" << s << "," << i << ")" << " 5 times gives a count of:\n";

  HashTable<int> table;
  table.SetSize(10);

  table.Add(s, i);
  table.Add(s, i);
  table.Add(s, i);
  table.Add(s, i);
  table.Add(s, i);

  // Print out the count for s -- it should be 5!!
  cout << *table.Get(s) << "\n";
}


void static GetTest1(string t)
{
  cout << "--GetTest1--\n";
  cout << "Original t: " << t << "\n";

  HashTable<int> table;
  table.SetSize(10);

  // Add t to the table
  table.Add(t, 1);
  table.Add("Banana", 1);
  table.Add("Roman Citizenship", 1);
  table.Add("Kung Fu", 1);

  string TableOutput = table.PrintTable();

  int result = *table.Get(t);

  cout << "Get(t): " << result << "\n";
  cout << "   (The Entire Table):   \n";
  cout << TableOutput << "\n";
}


void static SizingTest1(int i)
{
  cout << "--SizingTest1--\n";

  HashTable<int> table;

  // Print default size
  cout << "DefaultSize = " << table.Size() << "\n";

  // Set size to i
  table.SetSize(i);

  // Print size again - should see change
  cout << "New_Size = " << table.Size() << "\n";
}

void static OccupancyTest1()
{
  cout << "--OccupancyTest1--\n";

   HashTable<int> table;
  table.SetSize(10);

  // Print default occupancy
  cout << "Default Occupancy = " << table.Occupancy() << "\n";

  // Add t to the table
  table.Add("Your father is a", 1);
  table.Add("damned dirty ape. Also,", 1);
  table.Add("Graduation seems really far away.", 1);

  // Print out occupancy after 3 adds -- should increase from default
  cout << "Should have occupancy of 3 -- " << table.Occupancy() << "\n";
}

// Tests what happens when FindNextOpen is called on
// a string already present
void static FindNextOpenTest1(string str)
{
  cout << "--FindNextOpenTest1--\n";

  HashTable<int> table;
  table.SetSize(5);

  int placementIndex = table.Hash(str);
  table.Add(str, 1);
  cout << "str placed @ index " << placementIndex << "\n";

  int nextIndex = table.FindNextOpen(str);
  cout << "FindNextOpen returns  " << nextIndex<< " when a string is\n";
  cout << "already in the Hash Table\n";
}

// Hashes and places two different strings and reports on
// where they are in the table.
void static FindNextOpenTest2(string str)
{
  cout << "--FindNextOpenTest2--\n";

  HashTable<int> table;
  table.SetSize(5);

  int placementIndex = table.Hash(str);
  table.Add(str, 1);
  cout << str << " placed @ index " << placementIndex << "\n";

  string str2 = "indian food";
  int nextIndex = table.FindNextOpen(str2);			      
  table.Add(str2, 1);
  cout << "NextOpen for " << str2 << " is index " << nextIndex << "\n";

  string display = table.PrintTable();
  cout << "   <<Table>>\n";
  cout << display << "\n";
}

void static HashTest1(string s)
{
  HashTable<int> table;
  table.SetSize(10);

  /* Hash a string twice and see if the hash value is the same */
  int Hash1 = table.Hash(s);
  int Hash2 = table.Hash(s);

  cout << "The same string gets hashed to the same hash value:\n";
  cout << (Hash1 == Hash2) << "\n";
}


void static RehashTest1()
{
  HashTable<int> table;
  table.SetSize(5);


  cout << "--RehashTest1--\n";
  cout << "Original Size = " << table.Size() << endl;


  table.Add("U", 1);
  table.Add("V", 1);
  table.Add("W", 1);
  table.Add("X", 1);
  table.Add("Y", 1);
  table.Add("Z", 1);

  cout << "Table Filled! New Size = " << table.Size() << endl;
}

void static DumpEntriesTest1()
{
  cout << "--Dumping Entries!!--\n";

  HashTable<int> table;
  table.Add("A", 1);
  table.Add("B", 1);
  table.Add("C", 1);

  vector<HashTable<int>::Entry> e = table.DumpEntries();

  for (int i = 0; i < e.size(); i++)
    {
      HashTable<int>::Entry entry = e[i];
      cout << entry.key << "\n";
    }
}
