#include "ostream13.h"

using namespace std;

OStream13::OStream13() {}

void OStream13::create(char *filename) {
  int ofile = _open(filename, _O_WRONLY);
  if (ofile == -1) {
    cout << "Error";
    exit(1);
  }
  ofile1 = ofile;
}

void OStream13::write(int *elems) {
  int i = 0;
  while (i < sizeof(elems) / sizeof(elems[i]) and
         (_write(ofile1, &elems[i], sizeof(elems[i])) > 0)) {
    cout << elems[i] << endl;
    i++;
  }
}

void OStream13::close() { _close(ofile1); }
