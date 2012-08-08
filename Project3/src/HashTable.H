#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath> 
#include <vector>
#include <map>


//using namespace std;

/*
 * Author: Bailey Malone
 * Team Exception
 * Purpose: CS 3505, S12
 */

/* 
 * NOTE:
 * The classes were unable to compile unless the template_implementations
 * were included in the header file for the HashTable.
 * HashTable.C is not obsolete. .H/.C separation only worked (for me) for 
 * classes that were not template classes!
 */

/* DEBUG VALUE for Default_Size!!!! */
#define Default_Size 700

template <class T>class HashTable
{
typedef std::map< std::string , int > Test_Hash;
public:
  struct Entry {
    std::string key;
    int value;
  };

private:
  // int size;
  // int occupied;
  // Entry *array;
  // std::map<std::string, T> test_hash; 
  Test_Hash test_hash;

public:
  // HashTable()
  // {
    
  //   this->array = new Entry[Default_Size];

  //   this->size = 700;
  //   this->occupied = 0;
  // }
  // ~HashTable()
  // {
  //   this->size = 0;
  //   this->occupied = 0;

  //   delete [] array;
  //   array = 0;
  // }


  /* ******************************* */
  /* Method Defintions for HashTable */
  /* ******************************* */

  /* *** HashTable Methods *** */
  // int Size()
  // { return this->size; }

  int Occupancy()
  { return test_hash.size(); }

  // void SetSize(int i)
  // { this->size = i; }

  /*
   * Adds the Object to the table.
   */
  void Add(std::string key, int t)
  {
    test_hash[key] = t;

    // // Find the next open spot on the table
    // int NextOpen = this->FindNextOpen(key);

    // // IF the addee is already in the table...
    // if (NextOpen == -1)
    //   {
    // 	this->array[NextOpen].value = t; // Overwrite the value
    //   }
    // else
    //   {
    // 	// Place it in the empty spot
    // 	this->array[NextOpen].key = key;
    // 	this->array[NextOpen].value = t;
    // 	this->occupied += 1;
    //   }

    // // If the load-balance has reached ~75%, rehash the table
    // double LoadBalance = ((double)this->Occupancy() / this->Size());

    // if (LoadBalance >= 0.70)
    //   this->Rehash();
  }

  /*
   * Returns a pointer to the object stored in the table 
   * at the parameter index.
   *
   * Searches the table in quadratic-steps.
   */
  // NOTE:
  // This gets a *string* from the hashtable. Because generic types cannot
  // be compared together, this function also has to be overloaded for
  // support of other types.
 int Get(std::string s)
  {
    if(!test_hash.count(s)){
      return 0;
    }
    return test_hash[s];

    // // Hash the string to get the integer_index
    // int currentPos = this->Hash(s);
    // int origin = currentPos;
    // int adjustmentRoot = 1;


    // do
    //   {
    // 	if (this->array[currentPos].key == s)
    // 	  return &(this->array[currentPos].value);

    // 	currentPos += 1;
    // 	adjustmentRoot += 1;

    // 	/* Although cP is an int, Hash() checks for table conditions */
    // 	/*$$Sometimes this throws seg faults.... mod by table size instead?$$*/
    // 	if (currentPos >= this->Size())
    // 	  currentPos -= this->Size();
		
    //   } while(currentPos != origin);

    // return NULL;
  }

  /*
   * Find the next open spot in the table near the hash of
   * he's Entry's value (string).
   * *** Meant to be called in Add()....

   * *** Implements "Quadratic Probing"
   *
   * Needs to be overloaded for other types of Values that are
   * NOT strings.
   */
  /*********************************************************
   * UNADULTERATED SOURCE:
   * This algorithm is adapted from one written in Java by
   * Mark Weiss in "Data Structures and Problem Solving using 
   * JAVA".
   * *******************************************************
   */
  // int FindNextOpen(std::string str)
  // {
  //   // Initial Position
  //   int currentPos = this->Hash(str);
  //   int adjustmentRoot = 1;

  //   do
  //     {
  // 	// See if this element is already in the table
  // 	// If it is --> **Return a signature value (-1)**
  // 	//if (str.compare(*(this->array[currentPos])) == 0)
 
  //       if (this->array[currentPos].key == str)
  // 	  return -1;


  // 	// Else -- move to next
  // 	currentPos += (int)pow(adjustmentRoot, 2);
  // 	adjustmentRoot += 1;

  // 	/* Although cP is an int, Hash() checks for table conditions */
  // 	currentPos = this->Hash(currentPos);


  //     } while(this->array[currentPos].key != "");

 
  //   return currentPos;
  // }

  // /*
  //  * Returns the hash_code integer for a given string.
  //  *
  //  * NOTE --> To be improved over time as time allows.
  //  */
  // /*
  //  * Information source (for making hash functions) is
  //  * the Wikipedia page for "Hash Function."
  //  * 64 is an arbitrary constant meant to shift bits only 
  //  * slightly.
  //  */
  // int Hash(std::string str)
  // {
  //   int tableSize = this->Size();

  //   int hashCode = 0;

  //   // Make the hash_code int from the specific characters
  //   // in the std::stringsince, for natural language input data,
  //   // that is likely to be the only unique identifier for
  //   // words. (Which means that hash function will have more 
  //   // unique outputs).
  //   for (unsigned int i = 0; i < str.length(); i++)
  //     {
  // 	hashCode = (64 * hashCode) + str[i];
  //     }

  //   // Make sure the hash_code fits in the table's range
  //   hashCode = hashCode % tableSize;

  //   // Overflow might happen -- if it does, we will have a
  //   // negative hash_code.
  //   if (hashCode < 0)
  //     hashCode += tableSize;


  //   return hashCode;
  // }

  // int Hash(int x)
  // {
  //   int tableSize = this->Size();

  //   int hashCode = x;


  //   // Make sure the hash_code fits in the table's range
  //   hashCode = hashCode % tableSize;

  //   // Overflow might happen -- if it does, we will have a
  //   // negative hash_code.
  //   if (hashCode < 0)
  //     hashCode += tableSize;


  //   return hashCode;
  // }


  // /*
  //  * Creates a new HashTable larger than the calling one,
  //  * carrying elements over.
  //  */
  // void Rehash()
  // {
  //   int newSize = 2 * this->Size();
  //   int tempSize = this->Size();
  //   this->SetSize(newSize);
  //   Entry* temp = this->array;
  //   this->array = new Entry[newSize];
  
  //   for (int i = 0; i < tempSize; i++) {
  //     this->array[i] = temp[i];
  //   }
  //   delete [] temp;
  //   temp = 0;
  // }

  // /*
  //  * Creates a std::stringof every entry in the table.
  //  * Entries in the table are separated by newlines.
  //  */
  // std::string PrintTable()
  // {
  //   std::string s = "";
  //   std::string temp;
  //   for (int i = 0; i < this->Size(); i++)
  //     {
  // 	temp = this->array[i].key;

  // 	//if (temp == ""|| temp.empty())
  // 	if (temp.empty());
  // 	  //s += string("   ") + string("---\n");
  // 	else
  // 	  s += "   " + temp + "\n";
  //     }

  //   return s;
  // }

  std::vector<std::string> Keys()
  {
    std::vector<std::string> keys;

    //std::map<std::string, T>::const_iterator itr;
    for(Test_Hash::iterator itr = test_hash.begin(); itr != test_hash.end(); ++itr){
      keys.push_back((*itr).first);
    }
    
    return keys;
  }

  // /*
  //  * Returns a vector of Entry objects for (all 
  //  * of the nonempty Entries in the HashMap).
  //  *
  //  * It is *to be expected* that this returned vector is
  //  * OBSOLETE after the HashMap is modified!!
  //  */
  std::vector<Entry> DumpEntries()
  {
    std::vector<Entry> entries;

    // std::string temp;
    // for (int i = 0; i < this->Size(); i++)
    //   {
    // 	temp = this->array[i].key;

    // 	if (temp.empty());
    // 	else
    // 	  entries.push_back(this->array[i]);
  //     }

    //new for
    Test_Hash::const_iterator itr;
    for(itr = test_hash.begin(); itr != test_hash.end(); ++itr){
      Entry e = {(*itr).first, (*itr).second};
      entries.push_back(e);
    }
	    
     return entries; 
  }
};
#endif
