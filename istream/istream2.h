#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;

class IStream2 {
private:
FILE *ifile2;
int buffer;

public:
IStream2();

void open(char *filename);
int read_next();
bool end_of_stream();
};
