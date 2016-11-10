#include "istream2.h"

using namespace std;

IStream2::IStream2() {}

void IStream2::open(char *filename) {
    FILE *ifile;

    ifile = fopen(filename, "rb");

    if (ifile == NULL) {
        cout << "Error not existing";
        exit(1);
    }

    ifile2 = ifile;
}

int IStream2::read_next() {
    // size_t size;
    // size_t result;

    // //get file size
    // fseek(ifile, 0, SEEK_END);
    // size = ftell(ifile);
    // rewind(ifile);
    //
    // //allocate memory buffer
    // buffer = new char[size];

    //put the file content into the buffer

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
