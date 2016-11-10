#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class IStream2 {
private:

public:
IStream2();

FILE * open(char *filename);
char read_next(FILE *ifile);
bool end_of_stream(FILE *ifile);
};
