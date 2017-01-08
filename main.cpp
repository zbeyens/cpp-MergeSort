#include "istream/istream13.h"
#include "istream/istream2.h"
#include "istream/istream4.h"
#include "merge.h"
#include "ostream/ostream13.h"
#include "ostream/ostream2.h"
#include "ostream/ostream4.h"
#include <boost/chrono.hpp>
#include <cstdlib>
#include <fstream>
#include <io.h>
#include <iostream>
#include <math.h>
#include <string>
#include <utility>

using namespace std;
using namespace boost::chrono;

// param 1: method
// param 2: factorB
// param 3: k (max 30)
// param 4: repeat number for an average
// param 8: number of int to read (for method 1 and 2)

char *genFilename(string filename);
void countKmax();
void method13open(char *fn, char *fno, int B, vector<IStream13> &istreams,
                  vector<OStream13> &ostreams);
void method2open(char *fn, char *fno, vector<IStream2> &istreams,
                 vector<OStream2> &ostreams);
void method4open(char *fn, char *fno, int factorB, vector<IStream4> &istreams,
                 vector<OStream4> &ostreams);
void method13(IStream13 &reader13, OStream13 &writer13, int N);
void method2(IStream2 &reader2, OStream2 &writer2, int N);
void method4(IStream4 &reader4, OStream4 &writer4);

char *genFilename(string filename) {
  return const_cast<char *>(filename.c_str());
}

void countKmax() {
  int count = 0;
  ofstream *f;
  do {
    string fn = to_string(count++);
    f = new ofstream(fn);
  } while (*f << "test" << flush);
  --count; // last iteration failed to open the file.

  cout << "Your computer can open " << count << " streams" << endl;
}
void method13open(char *fn, char *fno, int B, vector<IStream13> &istreams,
                  vector<OStream13> &ostreams) {
  IStream13 reader13(B);
  reader13.open(fn);
  istreams.push_back(reader13);
  OStream13 writer13;
  writer13.create(fno);
  ostreams.push_back(writer13);
}

void method2open(char *fn, char *fno, vector<IStream2> &istreams,
                 vector<OStream2> &ostreams) {
  IStream2 reader2 = IStream2();
  reader2.open(fn);
  istreams.push_back(reader2);
  OStream2 writer2;
  writer2.create(fno);
  ostreams.push_back(writer2);
}

void method4open(char *fn, char *fno, int factorB, vector<IStream4> &istreams,
                 vector<OStream4> &ostreams) {
  IStream4 reader4(factorB);
  reader4.open(fn);
  istreams.push_back(reader4);
  OStream4 writer4;
  writer4.create(fno);
  ostreams.push_back(writer4);
}

void method13(IStream13 &reader13, OStream13 &writer13, int N) {
  int n = 0;

  while (!reader13.end_of_stream() && n != N) {
    vector<int> newElem = reader13.read_next();
    writer13.write(newElem);
    n++;
  }
  writer13.close();
}

void method2(IStream2 &reader2, OStream2 &writer2, int N) {
  int n = 0;

  while (!reader2.end_of_stream() && n != N) {
    int newElem = reader2.read_next();
    writer2.write(newElem);
    n++;
  }
  writer2.close();
}

void method4(IStream4 &reader4, OStream4 &writer4) {
  while (!reader4.end_of_stream()) {
    vector<int> newElem = reader4.read_next();
    writer4.write(newElem);
  }
  writer4.close();
}

int main(int argc, char *argv[]) {
  // if (argc != 4) {
  //     cout << "Choose a method read(1-4) in parameter 3" << endl;
  //     return 0;
  // }

  // parameters
  int method = atoi(argv[1]);
  int factorB = atoi(argv[2]);
  int B = factorB * 65536 / 4;
  cout << "Method " << atoi(argv[1]) << ", B = " << B << endl;
  int k = atoi(argv[3]);
  int repeat = atoi(argv[4]);
  int N = atoi(argv[8]);

  if (method == 0) {
    countKmax();
  }

  // start chrono
  high_resolution_clock::time_point start = high_resolution_clock::now();

  // read k streams and write them, N times

  for (int r = 0; r < repeat; r++) {
    if (method == 1 || method == 3) {
      vector<IStream13> istreams;
      vector<OStream13> ostreams;

      for (int i = 0; i < k; i++) {
        string filename = "filegen/" + to_string(i + 1) + ".bin";
        char *fn = genFilename(filename);
        filename = "filegen/o" + to_string(i + 1) + ".bin";
        char *fno = genFilename(filename);

        if (method == 1) {
          method13open(fn, fno, 0, istreams, ostreams);
        } else if (method == 3) {
          method13open(fn, fno, B, istreams, ostreams);
        }
      }

      for (int i = 0; i < k; i++) {
        cout << "Sample " << r << ": reading " << i << endl;
        method13(istreams[i], ostreams[i], N);
      }
    } else if (method == 2) {
      vector<IStream2> istreams;
      vector<OStream2> ostreams;

      for (int i = 0; i < k; i++) {
        string filename = "filegen/" + to_string(i + 1) + ".bin";
        char *fn = genFilename(filename);

        filename = "filegen/o" + to_string(i + 1) + ".bin";
        char *fno = genFilename(filename);
        method2open(fn, fno, istreams, ostreams);
      }

      for (int i = 0; i < k; i++) {
        cout << "Sample " << r << ": reading " << i << endl;
        method2(istreams[i], ostreams[i], N);
      }
    } else if (method == 4) {
      vector<IStream4> istreams;
      vector<OStream4> ostreams;

      for (int i = 0; i < k; i++) {
        string filename = "filegen/" + to_string(i + 1) + ".bin";
        char *fn = genFilename(filename);
        filename = "filegen/o" + to_string(i + 1) + ".bin";
        char *fno = genFilename(filename);
        method4open(fn, fno, factorB, istreams, ostreams);
      }

      for (int i = 0; i < k; i++) {
        cout << "Sample " << r << ": reading " << i << endl;
        method4(istreams[i], ostreams[i]);
      }
    }
  }

  milliseconds ms =
      duration_cast<milliseconds>(high_resolution_clock::now() - start);
  cout << "Took " << ms.count() << "ms" << endl;

  //---------------Part3------------------------------
  // param 5: M: size of the main memory available (first sort phase)
  // param 6: d: the number of streams to merge in one pass (in the later sort
  // phases)
  // param 7: file input
  high_resolution_clock::time_point start2 = high_resolution_clock::now();
  if (method == 5) {
    int N;                        // size of the file in 32 bits integer
    static int M = atoi(argv[5]); // size of a stream in 32 bits integer
    int d = atoi(argv[6]);        // number of streams to merge
    char *input_file = argv[7];

    queue<OStream13> stream_ref;
    vector<int> output;
    // reader and writer initialization
    IStream13 reader3(M);
    reader3.open(input_file);
    // find N and n
    N = int(reader3.get_length() / 4);
    int n = ceil(N / M); // number of streams
    cout << "M = " << M << ", d = " << d << endl;
    cout << "file length = " << reader3.get_length() << ", N = " << N
         << ", nbstreams= " << n << endl;

    // 1.sort each stream
    reader3.set_pointer(0);

    // N/M times
    for (int i = 0; i < n; i++) {
      // read and sort M element of the input file
      if (!reader3.end_of_stream()) {
        // cout << endl << "Split i = " << i << endl;
        vector<int> sequence = reader3.read_next();
        // cout << "sequence size = " << sequence.size() << endl;
        sort(sequence.begin(), sequence.end());

        // for (size_t j = 0; j < sequence.size(); j++) {
        //     cout << sequence[j] << ",";
        // }

        // create a stream of M element
        string filename = "file" + to_string(i) + ".bin";
        char *name = genFilename(filename);
        OStream13 writer;
        writer.create(name);
        writer.write(sequence);
        stream_ref.push(writer);
        // cout << stream_ref.front() << ",,," << endl;
      }
    }

    // WTF ?
    // cout << stream_ref.size() << ",,," << endl;

    // merge and sort every streams
    int l = 0;
    int x = (int)stream_ref.size();
    // cout << "ready for merging" << endl;

    while (x > 1) {
      // verify if 1) x < d 2) the pointer of the stream isn't bigger than the
      // file length
      int s = d;

      if (x < s) {
        // cout << "last merge" << endl;
        s = x;
      }

      vector<vector<int>> sequence_to_merge;

      for (int p = 0; p < s; p++) {
        OStream13 writer2 = stream_ref.front();
        stream_ref.pop();
        string filename = writer2.get_filename();
        IStream13 reader;
        // cout << "opening " << filename << endl;
        reader.open(genFilename(filename));
        int length = reader.get_length();
        reader.set_B(length);

        if (!reader.end_of_stream()) {
          sequence_to_merge.push_back(reader.read_next());
        }
        writer2.close();
      }

      OStream13 writer3;
      string filename = "file_merged" + to_string(l) + ".bin";

      if (s == x) {
        filename = "final_file.bin";
      }

      char *name = new char[filename.length() + 1];
      strcpy(name, filename.c_str());
      // do stuff
      writer3.create(name);
      // delete[] name;
      stream_ref.push(writer3);
      l += 1;
      s = d;
      x = (int)stream_ref.size(); // number of stream to merge
      // cout << "stremref len = " << x << endl;
      output = merge_sort(sequence_to_merge);
      // cout << "output merged -> length = " << output.size() << endl;
      writer3.write(output);

      // for (unsigned int i = 0; i < output.size(); i++) {
      //   cout << output[i] << endl;
      // }
      cout << "output written" << endl;
      output.clear();
    }
    milliseconds ms2 =
        duration_cast<milliseconds>(high_resolution_clock::now() - start2);
    cout << "Part3 took : " << ms2.count() << "ms" << endl;
  }

  return 0;
}
