#include "ostream4.h"

using namespace std;

OStream4::OStream4() {}

void OStream4::create(char *filename) {
    ofile4 = mapped_file_sink();
    param.path = filename;
    param.flags = mapped_file::mapmode::readwrite;
    file_name = string(filename);
    offs = 0;
}

void OStream4::write(vector<int> elems) {
    int elems_size = static_cast<int>(elems.size());
    param.new_file_size = elems_size * 4;
    param.offset = offs;

    ofile4.open(param);

    buffer = (int *)ofile4.data();
    copy(elems.begin(), elems.end(), buffer);

    offs += 4 * elems_size;
    ofile4.close();
}

void OStream4::close() {
    ofile4.close();
}

void OStream4::set_pointer_w(int place) {
    offs = place;
}

string OStream4::get_filename() {
    return file_name;
}
