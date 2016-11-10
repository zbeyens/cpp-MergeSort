#include "istream1.h"
using namespace std;

IStream1::IStream1() {}

void IStream1::open(char *filename) {
    descriptor = _open(filename, _O_RDONLY);

    if (descriptor == -1) {
        // fputs("File error", stderr);
        cout << "Error not existing";
        exit(1);
    }
}

int IStream1::read_next() {
    return *((int*) buffer);
}

bool IStream1::end_of_stream() {
    bool isEOF = false;

    if (_read(descriptor,buffer,4) <= 0) {
        _close(descriptor);
        isEOF = true;
    }

    return isEOF;
}
