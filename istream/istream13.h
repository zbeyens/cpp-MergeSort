#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

class IStream13 {
private:
  int current;
  int length;
  int ofile1;
  int B;
  char *buffer;

public:
  IStream13(int b);
  IStream13();
  void open(char *filename);
  int *read_next();
  bool end_of_stream();
};
