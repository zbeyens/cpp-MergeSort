#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class OStream2 {
private:
  FILE *ofile2;

public:
  OStream2();

  void create(char *filename);
  void write(int elem);
  void close();
};
