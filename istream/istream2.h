#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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
