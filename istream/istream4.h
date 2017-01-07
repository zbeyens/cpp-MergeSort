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
int offs;     //Mapped portion offset
int len;     //Mapped file's full length
mapped_file_source ifile4;
mapped_file_params param;
int factorB;
int B;
int Bcurrent;
int *buffer;

public:
IStream4(int b);
void open(char *filename);
std::vector<int> read_next();
bool end_of_stream();
int get_length();
};
