#include "istream/istream13.h"
#include "istream/istream2.h"
#include "istream/istream4.h"
#include "merge.h"
#include "ostream/ostream13.h"
#include "ostream/ostream2.h"
#include <cstdlib>
#include <io.h>
#include <iostream>
#include <utility>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Choose a method (1-4) in parameter 3";
        return 0;
    }

    //-----------------FIRST METHOD-----------------
    static int B = 2;

    if (argv[3][0] == '1') {
        cout << "First method" << endl;
        IStream13 reader1;
        OStream13 writer1;
        reader1.open(argv[1]);
        writer1.create(argv[2]);

        while (!reader1.end_of_stream()) {
            vector<int> res = reader1.read_next();

            writer1.write(res);
        }
        writer1.close();
    }

    //-----------------SECOND METHOD-----------------

    if (argv[3][0] == '2') {
        cout << endl << "Second method" << endl;
        IStream2 reader2;
        OStream2 writer2;
        reader2.open(argv[1]);
        writer2.create(argv[2]);

        while (!reader2.end_of_stream()) {
            int res = reader2.read_next();
            writer2.write(res);
            cout << res << endl;
        }
        writer2.close();
    }

    //-----------------THIRD METHOD-----------------

    if (argv[3][0] == '3') {
        cout << endl << "Third method" << endl;
        IStream13 reader3(B);
        OStream13 writer3;
        reader3.open(argv[1]);
        writer3.create(argv[2]);

        while (!reader3.end_of_stream()) {
            vector<int> res = reader3.read_next();
            writer3.write(res);
        }
        writer3.close();
    }

    //-----------------FOURTH METHOD-----------------

    if (argv[3][0] == '4') {
        cout << endl << "Fourth method" << endl;
        IStream4 reader4(B);
        // OStream4 writer4;
        reader4.open(argv[1]);
        // writer4.create(argv[2]);

        while (!reader4.end_of_stream())
            vector<int> res = reader4.read_next();
        // writer4.write(res);
        // writer4.close();
        // writer4.close();
    }

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
