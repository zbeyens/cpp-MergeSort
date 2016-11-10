#include "istream1.h"
using namespace std;

IStream1::IStream1() {}

void IStream1::open(char *filename) {
    int ofile = _open(filename, _O_RDONLY);

    if (ofile == -1) {
        cout << "Error not existing";
        exit(1);
    }

    ofile1 = ofile;
}

int IStream1::read_next() {
    return *((int *)buffer);
}

bool IStream1::end_of_stream() {
    bool isEOF = false;

    if (_read(ofile1, buffer, 4) <= 0) {
        _close(ofile1);
        isEOF = true;
    }

    return isEOF;
}
