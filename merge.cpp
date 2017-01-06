#include "merge.h"

void merge_sort(vector<vector<int>> listOfStreams, vector<int> *output) {
  priority_queue<Element, vector<Element>, Comp> min_heap;
  for (unsigned int i = 0; i < listOfStreams.size(); i++) {
    if (!listOfStreams[i].empty()) {

      Element elem;
      elem.x = i;
      elem.value = listOfStreams[i][0];
      // cout << "value :" << elem.value << endl;
      min_heap.push(elem);
    }
  }
  if (!min_heap.empty()) {
    Element min = min_heap.top();
    int value = min.value;
    // cout << "minimum: " << value << endl;
    output->push_back(value);
    listOfStreams[min.x].erase(listOfStreams[min.x].begin());
    merge_sort(listOfStreams, output);
  }
}
