#include "ostream13.h"
#include "sys/stat.h"

OStream13::OStream13() {}

void OStream13::create(char *filename) {
  int ofile = _open(filename, _O_WRONLY | _O_BINARY | _O_CREAT);

  if (ofile == -1) {
    cout << "Error";
    exit(1);
  }
  file_name = string(filename);

  ofile13 = ofile;
}

void OStream13::write(vector<int> elems) {
  _write(ofile13, &elems[0], elems.size() * 4);
}

void OStream13::close() { _close(ofile13); }

string OStream13::get_filename() { return file_name; }
