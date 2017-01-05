#include <fcntl.h>
#include <io.h>
#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
using namespace boost::iostreams;

class OStream4 {
private:
  int offs;     //Mapped portion offset
  mapped_file_sink ofile4;
  mapped_file_params param;
  int B;
  int *buffer;

public:
  OStream4();

  void create(char *filename);
  void write(std::vector<int> elem);
  void close();
  void set_pointer_w(int place);
};
