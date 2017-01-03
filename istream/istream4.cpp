#include "istream4.h"
using namespace std;

IStream4::IStream4(int b) {
    B = b;
    Bcurrent = 0;
    offset = 0;
    buffer = new int[B];
}

void IStream4::open(char *filename) {
    ifile4 = mapped_file_source();
    param.path = filename;

    //first, we map the entire file to store its length
    ifile4.open(param);

    if (!ifile4.is_open()) {
        cout << "Error not existing";
        exit(1);
    }

    length = ifile4.size();
    ifile4.close();
    cout << length << endl;
}

vector<int> IStream4::read_next() {
    vector<int> element(Bcurrent);

    cout << "B :" << Bcurrent << endl;
    buffer = (int *)ifile4.data();

    for (int i = 0; i < Bcurrent; i++) {
        element[i] = buffer[i];
        cout << element[i] << endl;
    }

    ifile4.close();
    return element;
}

bool IStream4::end_of_stream() {
    bool isEOF = false;

    int bufferSize = 4 * B >= length - offset ? length - offset : 4 * B;
    Bcurrent = bufferSize / 4;
    //map bufferSize bytes at the specific offset
    cout << bufferSize << ":" << offset << endl;

    if (bufferSize < 4) {
        cout << " whut";
        isEOF = true;
    } else {
        cout << bufferSize << ":" << offset << ":" << ifile4.alignment() << endl;
        param.length = bufferSize;
        param.offset = offset;
        // param.flags = mapped_file_base::mode::priv;
        // boost::intmax_t off = offset;
        ifile4.open(param);
        cout << "bug of offset ?" << endl;
        offset += bufferSize;
    }

    return isEOF;
}
