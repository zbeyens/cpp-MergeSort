#include "ostream2.h"

using namespace std;


void OStream2::create(char *filename) {
    FILE *ofile;

    ofile = fopen(filename, "wb");

    if (ofile == NULL) {
        cout << "Error not existing";
        exit(1);
    }

    ofile2 = ofile;
}

void OStream2::write(int elem) {
    fwrite(&elem, sizeof(int), 1, ofile2);
}

void OStream2::close() {
    fclose(ofile2);
}
