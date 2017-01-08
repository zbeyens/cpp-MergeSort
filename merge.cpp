#include "merge.h"

vector<int> merge_sort(vector<vector<int>> listOfStreams) {
  vector<int> output;
  priority_queue<Element, vector<Element>, Comp> min_heap;
  for (unsigned int i = 0; i < listOfStreams.size(); i++) {
    if (!listOfStreams[i].empty()) {
      Element elem;
      elem.x = i;
      elem.value = listOfStreams[i].front();
      min_heap.push(elem);
    }
  }
  while (!min_heap.empty()) {
    Element min = min_heap.top();
    min_heap.pop();
    int value = min.value;
    unsigned int index = min.x;
    // cout << "minimum: " << value << endl;
    output.push_back(value);
    listOfStreams[index].erase(listOfStreams[index].begin());
    if (!listOfStreams[index].empty()) {
      Element next;
      next.value = listOfStreams[index].front();
      next.x = index;
      min_heap.push(next);
    }
  }
  return output;
}
