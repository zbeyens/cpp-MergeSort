#include "istream13.h"
using namespace std;

IStream13::IStream13() {
    B = 1;
    offset = 0;
}

IStream13::IStream13(int b) {
    if (b == 0) {
        B = 1;
    } else {
        B = b;
    }

    offset = 0;
}

void IStream13::open(char *filename) {
    int ofile = _open(filename, _O_RDONLY);

    if (ofile == -1) {
        cout << "Error not existing";
        exit(1);
    }

    length = _lseek(ofile, 0, SEEK_END);
    _lseek(ofile, 0, SEEK_SET);

    ofile13 = ofile;
}

vector<int> IStream13::read_next() {
    char temp[4];
    vector<int> element(Bcurrent);

    for (int i = 0; i < Bcurrent; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j] = buffer[4 * i + j];
        }

        element[i] = *((int *)temp);
        // cout << element[i] << ",";
    }

    delete[] buffer;
    return element;
}

bool IStream13::end_of_stream() {
    bool isEOF = false;
    offset = _lseek(ofile13, 0, SEEK_CUR);

    int bufferSize = 4 * B >= length - offset ? length - offset : 4 * B;

    Bcurrent = bufferSize / 4;

    if (bufferSize == 0) {
        _close(ofile13);
        isEOF = true;
    } else {
        buffer = new char[bufferSize];
        _read(ofile13, buffer, bufferSize);
    }

    return isEOF;
}

int IStream13::get_length() {
    return length;
}

void IStream13::set_pointer(int place) {
    _lseek(ofile13, place, SEEK_SET);
}

void IStream13::set_B(int b) {
    B = b;
}
