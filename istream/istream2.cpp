#include "istream2.h"

using namespace std;

IStream2::IStream2() {}

FILE * IStream2::open(char *filename) { //char *filename
    FILE *ifile;

    ifile = fopen(filename, "r");

    if (ifile == NULL) {
        // fputs("File error", stderr);
        cout << "hh";
        exit(1);
    }

    return ifile;
}

char IStream2::read_next(FILE *ifile) {
    // char *buffer;
    // size_t size;
    // size_t result;

    // //get file size
    // fseek(ifile, 0, SEEK_END);
    // size = ftell(ifile);
    // rewind(ifile);
    //
    // //allocate memory buffer
    // buffer = new char[size];
    //
    // if (buffer == NULL) {
    //     fputs("Memory error", stderr);
    //     exit(2);
    // }
    // delete[] buffer;

    //put the file content into the buffer
    // fread(buffer, 1, 10, ifile);

    char buffer;
    buffer = fgetc(ifile);

    return buffer;
}

bool IStream2::end_of_stream(FILE *ifile) {
    bool isEOF = false;

    if (feof(ifile)) {
        fclose(ifile);
        isEOF = true;
    }

    return isEOF;
}
