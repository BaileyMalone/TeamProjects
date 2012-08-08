/*
 * BKTree.H
 * Team: Exception
 * Date: Spring 2012
 *
 */

#ifndef _BKTREE_H_
#define _BKTREE_H_

#include <string>
#include <vector>
#include <iostream>

void test_bktrees();

/** BKTree is used for fuzzy string searching.
 * By using the levenshtein distance to structure the tree, it is possible to 
 * query the tree for all words within a distance of a query word.
 *
 * The tree can be visualized using graphviz and the string from dot_string()
 */
class BKTree
{

public:
  void add(std::string word); // Add a word to the tree
  bool contains(std::string word); // Does the tree contain the given word?
  
  std::vector<std::string> get(std::string word, int count); // Try to get count suggestions for word.  Will never return more, may return fewer.
  std::string dot_string(); // Make a string suitable for use with graphviz dot
  BKTree();
  ~BKTree();

private:
  void resize(int to_accomodate); // Resize the children array to handle a child of this distance
  void dot_nodes_string(std::ostream &sstr); // Adds dot nodes describing the tree to a stream

  void get(std::vector<std::string> *results, std::string word, int tolerance=0); // Get a list of words at most tolerance edits away from word (default to exact match)
  bool root_set; // Has our word been set?
  std::string root; // Our word
  
  int child_capacity; // Size of children array
  BKTree **children; // Array of pointer to child BKTree*.  Index=Edit distance
};

#endif /* _BKTREE_H_ */
//EOF
