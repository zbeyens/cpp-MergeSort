#include "istream4.h"
using namespace std;

IStream4::IStream4(int b) {
    Bcurrent = 0;
    len = 0;
    offs = 0;
    factorB = b;
}

void IStream4::open(char *filename) {
    ifile4 = mapped_file_source();
    param.path = filename;

    //First, we map the entire file to store its length
    ifile4.open(param);

    if (!ifile4.is_open()) {
        cout << "Error not existing";
        exit(1);
    }

    //B must be a multiple of 65536
    B = factorB * ifile4.alignment() / 4;
    len = ifile4.size();
    ifile4.close();
}

vector<int> IStream4::read_next() {
    vector<int> element(Bcurrent);

    // cout << "We read the next B blocks (B = " << Bcurrent << ")" << endl;
    buffer = (int *)ifile4.data();

    for (int i = 0; i < Bcurrent; i++) {
        element[i] = buffer[i];
        // cout << "Integer #" << i << " : " << element[i] << endl;
    }

    ifile4.close();

    return element;
}

bool IStream4::end_of_stream() {
    bool isEOF = false;

    int bufferSize = 4 * B >= len - offs ? len - offs : 4 * B;
    Bcurrent = bufferSize / 4;
    //map bufferSize bytes at the specific offset
    // cout << "Buffer size of " << bufferSize << " with offset " << offs << endl;

    if (bufferSize == 0) {
        isEOF = true;
    } else {
        // cout << "alignment = " << ifile4.alignment() << endl;
        param.length = bufferSize;
        param.offset = offs;
        ifile4.open(param);
        offs += bufferSize;
    }

    return isEOF;
}

int IStream4::get_length() {
    return len;
}
