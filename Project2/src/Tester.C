#include <iostream>
#include <string>
#include <cstring>
#include "HashTable_Tester.H"
using namespace std;

/*
 * Author: Bailey Malone
 * Team Exception
 * Purpose: CS 3505, S12
 */

int main()
{
  HashTable<int> table;
  table.Add("A", 1);
  table.Add("B", 1);
  table.Add("C", 1);
  table.Add("X", 1);


  //int TableSize = sizeof(table);
  int TableSize = table.Size();
  cout << "Table_Size = " << TableSize << "\n";


  int p = *table.Get("X");
  cout << "Get(X): " << (p) << "\n";

  int str2 = *table.Get("B");
  cout << "Get(B): " << (str2) << "\n";

  // Should display "Entry Geronamo"
  AddTest1("Geronamo", 1);
  AddTest2("compile my shorts", 1);
  AddTest3("pantless dance party is not where my code is", 1);

  // Should
  GetTest1("A");

  // Sizing Test(s)
  SizingTest1(15);

  // OccupancyTest(s)
  OccupancyTest1();

  // FindNextOpenTest(s)
  FindNextOpenTest1("chinese food");
  FindNextOpenTest2("chinese food");

  // RehashTest(s)
  RehashTest1();

  // Dumping Entries Test
  DumpEntriesTest1();


  return 0;
}
