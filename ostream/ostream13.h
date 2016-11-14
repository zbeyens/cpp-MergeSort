#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdlib.h>

class OStream13 {
private:
  int ofile1;

public:
  OStream13();

  void create(char *filename);
  void write(int *elem);
  void close();
};
