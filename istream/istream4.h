#include <fcntl.h>
#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>
#include <stdlib.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
using namespace boost::iostreams;

class IStream4 {
private:
// char *ipath;
int offset;
int length;
mapped_file_source ifile4;
mapped_file_params param;
int B;
int Bcurrent;
int *buffer;

public:
IStream4(int b);
void open(char *filename);
std::vector<int> read_next();
bool end_of_stream();
};
