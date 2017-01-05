#include "ostream4.h"

using namespace std;

OStream4::OStream4() {}

void OStream4::create(char *filename) {
    ofile4 = mapped_file_sink();
    param.path = filename;
    ofile4.open(param);

    if (!ofile4.is_open()) {
        cout << "Error: output file not found." << endl;
        exit(1);
    }

    //B must be a multiple of 65536
    B = (ofile4.alignment() / 4);
    offs = 0;
    buffer = new int[B];
    ofile4.close();
}

void OStream4::write(vector<int> elems) {
    int elems_size = static_cast<int>(elems.size());
    param.length = elems_size;
    param.offset = offs;

    ofile4.open(param);

    buffer = (int *)ofile4.data();
    for (int i = 0; i < elems_size/4; i++) {
        buffer[i] = elems[i];
    }

    offs += 4*B;
    ofile4.close();
}

void OStream4::close() {
    ofile4.close();
}

void OStream4::set_pointer_w(int place) {
    offs = place;

}
