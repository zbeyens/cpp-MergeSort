#include "istream13.h"
using namespace std;

IStream13::IStream13(int b) {
  B = b;
  current = 0;
}
IStream13::IStream13() {
  B = 1;
  current = 0;
}

void IStream13::open(char *filename) {
  int ofile = _open(filename, _O_RDONLY);
  if (ofile == -1) {
    cout << "Error not existing";
    exit(1);
  }
  current = _lseek(ofile1, 0, SEEK_END);
  _lseek(ofile1, 0, SEEK_SET);

  ofile1 = ofile;
}

int *IStream13::read_next() {
  char temp[4];
  cout << B << endl;
  int element[B];
  int i;
  for (i = 0; i < B; i++) {
    for (int j = 0; j < 4; j++) {
      temp[j] = buffer[i + j];
      cout << buffer[i + j] << endl;
    }
    element[i] = *((int *)temp);
  }
  memset(buffer, 0, sizeof(buffer) / sizeof(buffer[0]));
  return element;
}

bool IStream13::end_of_stream() {
  bool isEOF = false;
  current = _lseek(ofile1, 0, SEEK_CUR);
  if (current < 0) {
  }
  if (4 * B >= length - current) {
    if (_read(ofile1, buffer, length - current) <= 0) {
    }
    _close(ofile1);
    isEOF = true;
  } else {
    if (_read(ofile1, buffer, 4 * B) <= 0) {
      _close(ofile1);
      isEOF = true;
    }
    current += 4 * B;
  }

  return isEOF;
}
