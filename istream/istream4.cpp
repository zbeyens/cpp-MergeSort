#include "istream4.h"
using namespace std;

IStream4::IStream4(int b) {
    B = b;
    offset = 0;
    buffer = new int[B];
}

void IStream4::open(char *filename) {

    ifile4 = mapped_file_source();
    ipath = filename;

    ifile4.open(ipath);
    //ifile4.open(filename, Bcurrent*4, 0)

    if (!ifile4.is_open()) {
        cout << "Error not existing";
        exit(1);
    }

    length = ifile4.size();
}

vector<int> IStream4::read_next() {
    vector<int> element(Bcurrent);

    cout << "B :" << Bcurrent << endl;
    buffer = (int *)ifile4.data();

    for (int i = 0; i < Bcurrent; i++) {
        element[i] = buffer[i];
        cout << " : " << element[i] << endl;
    }

    return element;
}

bool IStream4::end_of_stream() {

    bool isEOF = false;
    offset += Bcurrent*4;

    int bufferSize = 4 * B >= length - offset ? length - offset : 4 * B;
    Bcurrent = bufferSize / 4;
    ifile4.open(ipath, bufferSize, offset);

    if (bufferSize < 4 || !ifile4.is_open()) {
        ifile4.close();
        isEOF = true;
    }

    return isEOF;
}
