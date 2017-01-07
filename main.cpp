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
#include <math.h>
#include <string>
#include <utility>
#include <boost/chrono.hpp>
#include <fstream>

using namespace std;
using namespace boost::chrono;

// param 1: method
// param 2: factorB
// param 3: k
// param 4: N1: number of times to read

char * genFilename(string filename);
void countKmax();
void method1read(char *fn, vector<int> &stream);
void method2read(char *fn, vector<int> &stream);
void method3read(char *fn, vector<int> &stream, int B);
void method4read(char *fn, vector<int> &stream, int factorB);
void method1write(char *fn, vector<int> stream);
void method2write(char *fn, vector<int> stream);
void method13write(char *fn, vector<int> stream);
void method4write(char *fn, vector<int> stream);

char * genFilename(string filename) {
    return const_cast<char *>(filename.c_str());
}

void countKmax() {
    int count = 0;
    ofstream *f;
    do {
        string fn = to_string(count++);
        f = new ofstream(fn);
    } while (*f << "test" << flush);
    --count;   // last iteration failed to open the file.


    cout << "Your computer can open " << count  << " streams" << endl;
}

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

    if (method == 0) {
        countKmax();
    }

    //start chrono
    high_resolution_clock::time_point start = high_resolution_clock::now();

    //read k streams and write them, N times

    for (int n = 0; n < N; n++) {
        vector<vector<int> > streams;

        for (int i = 0; i < k; i++) {
            string filename = "filegen/" + to_string(i + 1) + ".bin";
            char *fn = genFilename(filename);
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
            char *fn = genFilename(filename);
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
    //param 5: M: size of the main memory available (first sort phase)
    //param 6: d: the number of streams to merge in one pass (in the later sort phases)
    //param 7: file input
    if (method == 5) {
        int N;                     // size of the file in 32 bits integer
        static int M = atoi(argv[5]); // size of a stream in 32 bits integer
        int d = atoi(argv[6]);     // number of streams to merge
        char *input_file = argv[7];

        queue<OStream13> stream_ref;
        vector<int> *output = new vector<int>;

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

        //N/M times
        for (int i = 0; i < n; i++) {
            //read and sort M element of the input file
            if (!reader3.end_of_stream()) {
                // cout << endl << "Split i = " << i << endl;
                vector<int> sequence = reader3.read_next();
                // cout << "sequence size = " << sequence.size() << endl;
                sort(sequence.begin(), sequence.end());

                // for (size_t j = 0; j < sequence.size(); j++) {
                //     cout << sequence[j] << ",";
                // }

                //create a stream of M element
                string filename = "file" + to_string(i) + ".bin";
                char *name = genFilename(filename);
                OStream13 writer;
                writer.create(name);
                writer.write(sequence);
                stream_ref.push(writer);
                cout << stream_ref.front().get_filename() << ",,," << endl;
            }
        }

        //WTF ?
        cout << stream_ref.size() << ",,," << endl;


        // merge and sort every streams
        int l = 0;
        int x = (int)stream_ref.size();
        cout << "ready for merging" << endl;

        while (x > 1) {
            // verify if 1) x < d 2) the pointer of the stream isn't bigger than the
            // file length
            int s = d;

            if (x < s) {
                cout << "last merge" << endl;
                s = x;
            }

            vector<vector<int> > sequence_to_merge;

            for (int p = 0; p < s; p++) {
                OStream13 writer = stream_ref.front();
                stream_ref.pop();
                IStream13 reader;
                cout << "opening " << writer.get_filename() << endl;
                reader.open(writer.get_filename());
                int length = reader.get_length();
                reader.set_B(length);

                if (!reader.end_of_stream()) {
                    sequence_to_merge.push_back(reader.read_next());
                }

                writer.close();
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
    }

    return 0;
}
