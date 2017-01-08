#include <iostream>
#include <iterator>
#include <queue>
#include <vector>
using namespace std;

struct Element {
  int value;
  unsigned int x;
};

struct Comp {
  bool operator()(const Element &a, const Element &b) {
    return a.value > b.value;
  }
};
vector<int> merge_sort(vector<vector<int>> listOfStreams);
