/*
 * BKTree.C
 * Team: Exception
 * Date: Spring 2012
 *
 */

// The vector and sort are only used to store and sort query output
// They aren't used to build the tree structure. That's all new and delete.
#include <vector>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#include "BKTree.H"

using namespace std;


/*// If you want a quick tree test exe, use this.
int main() {
  test_bktrees();
  return 0;
  }*/

int levenshtein(string word1, string word2)
{
  int n = word1.length() + 1;
  int m = word2.length() + 1;
  int *mat = new int[n * m]; // Distance matrix, solution will be in last cell

  // Following the algorithm from http://www.merriampark.com/ld.htm

  // Initialize first row
  for (int i = 0; i < n; i++) {
    mat[i] = i;
  }
  // Initialize first column
  for (int j = 0; j < m; j++) {
    mat[j*n] = j;
  }

  // Calculate the distance matrix
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      int a = 1 + mat[i + ((j - 1) * n)]; // 1 + above cell
      int b = 1 + mat[(i - 1) + (j * n)]; // 1 + left cell
      int c = (word1.at(i - 1) == word2.at(j - 1) ? 0 : 1) + mat[(i - 1) + ((j - 1) * n)]; // cost + up-left cell
      mat[i + (j * n)] = a > b ? (b > c ? c : b) : (a > c ? c : a); // current cell = min(a,b,c)
    }
  }

  // The last element is the total distance
  int result = mat[(n * m) - 1];

  delete [] mat;
  return result;
}

void test_bktrees()
{
  cout << "Testing levenshtein...";
  if (levenshtein("noon", "poon") != 1 ||
      levenshtein("poon", "spoon") != 1 ||
      levenshtein("spoon", "soon") != 1 ||
      levenshtein("soon", "sun") != 2 ||
      levenshtein("sun", "luna") != 2 ||
      levenshtein("luna", "lab") != 3 ||
      levenshtein("lab", "purple") != 6) {
    cout << "Error!" << endl;
  } else {
    cout << "Done!" << endl;
  }

  cout << "Testing BKTree fuzzy matching...";
  BKTree tree;
  tree.add("noon");
  tree.add("poon");
  tree.add("spoon");
  tree.add("soon");
  tree.add("sun");
  tree.add("luna");
  tree.add("lab");
  tree.add("purple");

  vector<string> results = tree.get("spoon", 5);
  if (results.size() != 5 ||
      strcmp("spoon", results[0].c_str()) ||
      strcmp("poon", results[1].c_str()) ||
      strcmp("soon", results[2].c_str()) ||
      strcmp("noon", results[3].c_str()) ||
      strcmp("sun", results[4].c_str())) {
    cout << "Error!" << endl;
  } else {
    cout << "Done!" << endl;
  }
  /*
  BKTree tree2;
  ifstream fin("words.txt");
  while (fin.good()) {
    string word;
    fin >> word;
    tree2.add(word);
  }
  fin.close();
  // If you are curious about what the tree looks like, and have graphviz, you'll like this next part.
  ofstream f("tree.dot");
  f << tree2.dot_string();
  f.close();
  */
}

void BKTree::add(string word)
{
  if (!root_set) {
    root_set = true;
    root = word;
  } else {
    int dist = levenshtein(root, word);
    if (dist >= child_capacity) {
      resize(dist);
    }
    if (children[dist] == NULL) {
      children[dist] = new BKTree();
    }
    children[dist]->add(word);
  }
}

void BKTree::resize(int to_accomodate)
{
  // There. Didn't use a vector. Happy?
  int new_size = child_capacity ? child_capacity : 1;

  while (new_size <= to_accomodate) {
    new_size *= 2;
  }

  BKTree **new_children = new BKTree*[new_size];
  memset(new_children, 0, sizeof(BKTree*) * new_size);
  
  if (child_capacity > 0) {
    memcpy(new_children, children, sizeof(BKTree*) * child_capacity);
    delete [] children;
  }
  
  children = new_children;
  child_capacity = new_size;
}

// Compares word based on levenshtein from a certain word
struct LevenshteinSorter
{
  string root;
  bool operator() (string word1, string word2)
  {
    return levenshtein(root, word1) < levenshtein(root, word2);
  }
  LevenshteinSorter(string root_word) : root(root_word) {}
};

bool BKTree::contains(string word)
{
  if (!root_set) {
    return false;
  }

  int dist = levenshtein(root, word);
  if (dist == 0) {
    return true;
  }
  
  if (dist < child_capacity && children[dist]) {
    return children[dist]->contains(word);
  }
  return false;
}

vector<string> BKTree::get(string word, int count)
{
  vector<string> results;
  
  for (int tolerance = 1; tolerance <= (int)word.size(); tolerance++) {
    results.clear();
    get(&results, word, tolerance);
    if ((int)results.size() >= count) {
      sort(results.begin(), results.end(), LevenshteinSorter(word));
      results.resize(count);
      return results;
    }
  }
  sort(results.begin(), results.end(), LevenshteinSorter(word));
  return results;
}

void BKTree::get(vector<string> *results, string word, int tolerance)
{
  int dist = levenshtein(root, word);
  if (dist <= tolerance) {
    results->push_back(root);
  }

  // Any word within tolerance is guaranteed to be down branches between (dist - tolerance) and (dist + tolerance).  Aren't BKTree's nifty?
  int min = dist - tolerance;
  int max = dist + tolerance;
  for (int i = (min > 0) ? min : 0; i <= (max < child_capacity - 1 ? max : child_capacity - 1); i++) {
    if (children[i]) {
      children[i]->get(results, word, tolerance);
    }
  }
}

BKTree::BKTree() : root_set(false), child_capacity(0), children(NULL) {}

BKTree::~BKTree()
{
  // delete doesn't try to delete null pointers.  Unused pointer should be set to null
  for (int i = 0; i < child_capacity; i++) {
    delete children[i];
  }
  delete [] children;
}

string BKTree::dot_string()
{
  ostringstream sstr;
  sstr << "digraph G {\n  splines=true;\n  overlap=false;" << endl;
  dot_nodes_string(sstr);
  sstr << "}" << endl;
  return sstr.str();
}

void BKTree::dot_nodes_string(ostream &sstr)
{
  sstr << "  \"" << root << "\" [style=filled, fillcolor=\"0.9 0.7 " << 1.0 / (levenshtein(root, string("merlins")) + 1.0) << "\"];" << endl;
  for (int i = 0; i < child_capacity; i++) {
    if (children[i]) {
      children[i]->dot_nodes_string(sstr);
      sstr << "  \"" << root << "\" -> \"" << children[i]->root << "\" [label=\"" << i << "\"];" << endl;
    }
  }
}
//EOF
