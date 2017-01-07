#include "istream2.h"


IStream2::IStream2() {}

void IStream2::open(char *filename) {
    ifile2 = fopen(filename, "rb");
}

int IStream2::read_next() {
    return buffer;
}

bool IStream2::end_of_stream() {
    bool isEOF = false;

    if (fread(&buffer, sizeof(int), 1, ifile2) <= 0) {
        fclose(ifile2);
        isEOF = true;
    }

    return isEOF;
}
