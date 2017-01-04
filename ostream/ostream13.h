#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

class OStream13 {
private:
  int ofile13;

public:
  OStream13();

  void create(char *filename);
  void write(std::vector<int> elem);
  void close();
  void set_pointer_w(int place);
};
