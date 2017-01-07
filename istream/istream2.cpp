#include "istream2.h"

using namespace std;

IStream2::IStream2() {}

void IStream2::open(char *filename) {
    FILE *ifile;

    fn = filename;
    ifile = fopen(filename, "rb");

    if (ifile == NULL) {
        cout << "Error not existing";
        exit(1);
    }

    ifile2 = ifile;
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

char * IStream2::get_filename() {
    return fn;
}
