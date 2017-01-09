#include "ostream2.h"

using namespace std;

OStream2::OStream2() {}

void OStream2::create(char *filename) {
    ofile2 = fopen(filename, "wb");

    if (ofile2 == NULL) {
        cout << "Error not existing";
        exit(1);
    }
}

void OStream2::write(int elem) {
    fwrite(&elem, sizeof(int), 1, ofile2);
}

void OStream2::close() {
    fclose(ofile2);
}
