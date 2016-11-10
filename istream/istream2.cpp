#include "istream2.h"

using namespace std;

IStream2::IStream2() {}

void IStream2::open(char *filename) { //char *filename
    FILE *ifile;

    ifile = fopen(filename, "rb");

    if (ifile == NULL) {
        // fputs("File error", stderr);
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
    int buffer;
    fread(&buffer, sizeof(int), 1, ifile2);

    return buffer;
}

bool IStream2::end_of_stream() {
    bool isEOF = false;

    if (feof(ifile2)) {
        fclose(ifile2);
        isEOF = true;
    }

    return isEOF;
}
