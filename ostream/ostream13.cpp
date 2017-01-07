#include "ostream13.h"
#include "sys/stat.h"

using namespace std;

OStream13::OStream13() {}

void OStream13::create(char *filename) {
    int ofile = _open(filename, _O_WRONLY | _O_BINARY | _O_CREAT);
    file_name = filename;

    if (ofile == -1) {
        cout << "Error";
        exit(1);
    }

    ofile13 = ofile;
}

void OStream13::write(vector<int> elems) {
    _write(ofile13, &elems[0], elems.size() * 4);
}

void OStream13::close() {
    _close(ofile13);
    free();
}

void OStream13::free() {
    delete[] file_name;
}

char * OStream13::get_filename() {
    return file_name;
}
