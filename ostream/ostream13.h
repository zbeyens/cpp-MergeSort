#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <vector>
using namespace std;
class OStream13 {
private:
  int ofile13;
  string file_name;

public:
  OStream13();

  void create(char *filename);
  void write(std::vector<int> elem);
  void close();
  string get_filename();
  void free();
};
