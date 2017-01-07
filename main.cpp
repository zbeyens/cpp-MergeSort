#include "istream/istream13.h"
#include "istream/istream2.h"
#include "istream/istream4.h"
#include "merge.h"
#include "ostream/ostream13.h"
#include "ostream/ostream2.h"
#include <cstdlib>
#include <io.h>
#include <iostream>
#include <math.h>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cout << "Choose a method (1-4) in parameter 3";
    return 0;
  }

  // //-----------------FIRST METHOD-----------------
  // static int B = 2;
  //
  // if (argv[3][0] == '1') {
  //   cout << "First method" << endl;
  //   IStream13 reader1;
  //   OStream13 writer1;
  //   reader1.open(argv[1]);
  //   writer1.create(argv[2]);
  //
  //   while (!reader1.end_of_stream()) {
  //     vector<int> res = reader1.read_next();
  //
  //     writer1.write(res);
  //   }
  //   writer1.close();
  // }
  //
  // //-----------------SECOND METHOD-----------------
  //
  // if (argv[3][0] == '2') {
  //   cout << endl << "Second method" << endl;
  //   IStream2 reader2;
  //   OStream2 writer2;
  //   reader2.open(argv[1]);
  //   writer2.create(argv[2]);
  //
  //   while (!reader2.end_of_stream()) {
  //     int res = reader2.read_next();
  //     writer2.write(res);
  //     cout << res << endl;
  //   }
  //   writer2.close();
  // }
  //
  // //-----------------THIRD METHOD-----------------
  //
  // if (argv[3][0] == '3') {
  //   cout << endl << "Third method" << endl;
  //   IStream13 reader3(B);
  //   OStream13 writer3;
  //   reader3.open(argv[1]);
  //   writer3.create(argv[2]);
  //
  //   while (!reader3.end_of_stream()) {
  //     vector<int> res = reader3.read_next();
  //     writer3.write(res);
  //   }
  //   writer3.close();
  // }
  //
  // //-----------------FOURTH METHOD-----------------
  //
  // if (argv[3][0] == '4') {
  //   cout << endl << "Fourth method" << endl;
  //   IStream4 reader4(B);
  //   // OStream4 writer4;
  //   reader4.open(argv[1]);
  //   // writer4.create(argv[2]);
  //
  //   while (!reader4.end_of_stream())
  //     vector<int> res = reader4.read_next();
  //   // writer4.write(res);
  //   // writer4.close();
  //   // writer4.close();
  // }

  //---------------Part3------------------------------

  // variable
  char *input_file = argv[1];
  int N;                        // size of the file in 32 bits integer
  static int M = atoi(argv[2]); // size of a stream in 32 bits integer
  int d = atoi(argv[3]);        // number of streams to merge

  queue<OStream13> stream_ref;
  vector<int> *output = new vector<int>;

  // reader and writer initialization
  IStream13 reader3(M);
  reader3.open(input_file);
  // find N and n
  N = int(reader3.get_length() / 4); //
  int n = ceil(N / M);               // number of streams
  cout << "M= " << M << ", d= " << d << endl;
  cout << "file length= " << reader3.get_length() << ", N= " << N
       << ", nbstreams= " << n << endl;

  // 1.sort each stream
  int j = 0;
  reader3.set_pointer(0);
  while (j < n) {
    if (!reader3.end_of_stream()) {
      cout << "j = " << j << endl;
      vector<int> sequence = reader3.read_next();
      cout << "sequence size = " << sequence.size() << endl;
      sort(sequence.begin(), sequence.end());
      OStream13 *writer = new OStream13();
      // choose name and convert into a char*
      string filename = "file" + to_string(j) + ".bin";
      char *name = new char[filename.length()];
      strcpy(name, filename.c_str());
      cout << name << endl;
      // create the file
      cout << " creation of " << name << " ..." << endl;
      writer->create(name);
      cout << "file created " << endl;
      // delete[] name;
      writer->write(sequence);
      // 2.store the reference
      stream_ref.push(*writer);
    }
    j += 1;
  }

  // merge and sort every streams
  int l = 0;
  int s = d;
  int x = (int)stream_ref.size();
  cout << "ready for merging" << endl;
  while (x > 1) {

    // verify if 1) x < d 2) the pointer of the stream isn't bigger than the
    // file length

    if (x < s) {
      s = x;
    }
    vector<vector<int>> sequence_to_merge(s);
    for (int k = 0; k < s; k++) {
      OStream13 writer2 = stream_ref.front();
      stream_ref.pop();
      IStream13 reader;
      cout << "open : " << writer2.get_filename() << endl;
      reader.open(writer2.get_filename());
      int length = reader.get_length();
      reader.set_B(length);
      if (!reader.end_of_stream()) {
        sequence_to_merge[k] = reader.read_next();
      }
      writer2.close();
    }
    OStream13 *writer3 = new OStream13();
    string filename = "file_merged" + to_string(l) + ".bin";
    if (s == x) {
      filename = "final_file.bin";
    }
    char *name = new char[filename.length() + 1];
    strcpy(name, filename.c_str());
    // do stuff

    writer3->create(name);
    // delete[] name;
    stream_ref.push(*writer3);
    l += 1;
    s = d;
    x = (int)stream_ref.size(); // number of stream to merge
    cout << "stremref len = " << x << endl;
    merge_sort(sequence_to_merge, output);
    cout << "output merged -> length = " << output->size() << endl;
    writer3->write(*output);
    cout << "output written" << endl;
    output->erase(output->begin(), output->end());
    cout << output->size() << endl;
  }

  return 0;
}
