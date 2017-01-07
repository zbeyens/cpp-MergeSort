#include "istream/istream13.h"
#include "istream/istream2.h"
#include "istream/istream4.h"
#include "merge.h"
#include "ostream/ostream13.h"
#include "ostream/ostream2.h"
#include "ostream/ostream4.h"
#include <cstdlib>
#include <io.h>
#include <iostream>
#include <utility>
#include <boost/chrono.hpp>

using namespace std;
using namespace boost::chrono;

// param 1: method
// param 2: factorB
// param 3: k
// param 4: N

void method1read(char *fn, vector<int> &stream);
void method2read(char *fn, vector<int> &stream);
void method3read(char *fn, vector<int> &stream, int B);
void method4read(char *fn, vector<int> &stream, int factorB);
void method1write(char *fn, vector<int> stream);
void method2write(char *fn, vector<int> stream);
void method13write(char *fn, vector<int> stream);
void method4write(char *fn, vector<int> stream);

void method1read(char *fn, vector<int> &stream) {
    method3read(fn, stream, 0);
}

void method2read(char *fn, vector<int> &stream) {
    IStream2 reader2;
    reader2.open(fn);

    while (!reader2.end_of_stream()) {
        int newElem = reader2.read_next();
        stream.push_back(newElem);
    }
}

void method2write(char *fn, vector<int> stream) {
    OStream2 writer2;
    writer2.create(fn);

    for (size_t i = 0; i < stream.size(); i++) {
        writer2.write(stream[i]);
    }

    writer2.close();
}

void method3read(char *fn, vector<int> &stream, int B) {
    IStream13 reader3(B);
    reader3.open(fn);

    while (!reader3.end_of_stream()) {
        vector<int> newElem = reader3.read_next();
        stream.insert(stream.end(), newElem.begin(), newElem.end());
    }
}

void method13write(char *fn, vector<int> stream) {
    OStream13 writer13;
    writer13.create(fn);
    writer13.write(stream);
    writer13.close();
}

void method4read(char *fn, vector<int> &stream, int factorB) {
    IStream4 reader4(factorB);
    reader4.open(fn);

    while (!reader4.end_of_stream()) {
        vector<int> newElem = reader4.read_next();
        stream.insert(stream.end(), newElem.begin(), newElem.end());
    }
}

void method4write(char *fn, vector<int> stream) {
    OStream4 writer4;
    writer4.create(fn);
    writer4.write(stream);
    writer4.close();
}

int main(int argc, char *argv[]) {
    // if (argc != 4) {
    //     cout << "Choose a method read(1-4) in parameter 3" << endl;
    //     return 0;
    // }

    //parameters
    int method = atoi(argv[1]);
    int factorB = atoi(argv[2]);
    int B = factorB * 65536 / 4;
    cout << "Method " << atoi(argv[1]) << ", B = " << B << endl;
    int k = atoi(argv[3]);
    int N = atoi(argv[4]);

    //start chrono
    high_resolution_clock::time_point start = high_resolution_clock::now();

    //read k streams and write them, N times
    for (int n = 0; n < N; n++) {
        vector<vector<int> > streams;

        for (int i = 0; i < k; i++) {
            string filename = "filegen/" + to_string(i + 1) + ".bin";
            char *fn = const_cast<char *>(filename.c_str());
            cout << "Sample " << n << ": reading " << fn << endl;
            vector<int> stream;

            if (method == 1) {
                method1read(fn, stream);
            } else if (method == 2) {
                method2read(fn, stream);
            } else if (method == 3) {
                method3read(fn, stream, B);
            } else if (method == 4) {
                method4read(fn, stream, factorB);
            }

            streams.push_back(stream);
        }

        for (int i = 0; i < k; i++) {
            string filename = "filegen/" + to_string(i + 1) + ".bin";
            char *fn = const_cast<char *>(filename.c_str());
            cout << "Sample " << n << ": writing " << fn << endl;

            if (method == 1 || method == 3) {
                method13write(fn, streams[i]);
            } else if (method == 2) {
                method2write(fn, streams[i]);
            } else if (method == 4) {
                method4write(fn, streams[i]);
            }
        }
    }

    milliseconds ms = duration_cast<milliseconds> (high_resolution_clock::now() - start);
    cout << "Took " << ms.count() << "ms" << endl;

    //---------------Part3------------------------------

    // // variable
    // int N;                        // size of the file in 32 bits integer
    // static int M = atoi(argv[4]); // size of a stream in 32 bits integer
    // int d = atoi(argv[5]);        // number of streams to merge
    // queue<pair<int, int>, vector<pair<int, int>>> stream_ref;
    // vector<int> *output = new vector<int>;
    //
    // // reader and writer initialization
    // IStream13 reader3(M);
    // reader3.open(argv[1]);
    // OStream13 writer;
    // writer.create(argv[1]);
    //
    // // find N and n
    // N = int(reader3.get_length() / 4); //
    // int n = int(N / M);                // number of streams
    // if (N % M != 0) {
    //   n += 1;
    // }
    //
    // // 1.sort each stream
    // int j = 0;
    // while (!reader3.end_of_stream()) {
    //   int pointer = 4 * j * M;
    //   vector<int> sequence = reader3.read_next();
    //   sort(sequence.begin(), sequence.end());
    //   writer.write(sequence);
    //   // 2.store
    //   stream_ref.push((pointer, M));
    //   j += 1;
    // }
    //
    // // merge and sort every streams
    // int l = 0;
    // while (stream_ref.size() > 1) {
    //
    //   int x = stream_ref.size(); // number of stream to merge
    //
    //   // verify if 1) x < d 2) the pointer of the stream isn't bigger than the
    //   // file length
    //
    //   if (x < d) {
    //     d = x;
    //   }
    //   if (l >= 4 * (N)) {
    //     l = 0;
    //   }
    //
    //   writer.set_pointer_w(l);
    //   vector<vector<int>> sequence_to_merge(d);
    //
    // int sizeStreams = 0;
    //
    // for (int k = 0; k < d; k++) {
    //     int pointer, int B = stream_ref.front();
    //     reader3.set_pointer(pointer);
    //     reader3.set_B(B);
    //
    //     if (!reader3.end_of_stream()) {
    //         sequence_to_merge[k] = reader3.read_next();
    //         sizeStreams += sequence_to_merge[k].size();
    //     }
    // }
    //
    // stream_ref.push((l, sizeStreams));
    // l += 4 * sizeStreams;
    //
    //   merge_sort(sequence_to_merge, output);
    //   writer.write(*output);
    //   output->erase(output->begin(), output->end());
    // }
    // writer.close();

    return 0;
}
