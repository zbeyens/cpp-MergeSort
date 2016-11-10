#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>

class IStream1 {
private:
int ofile1;
char buffer[4];

public:
IStream1();
void open(char *filename);
int read_next();
bool end_of_stream();
};
