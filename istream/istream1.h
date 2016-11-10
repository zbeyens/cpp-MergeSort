#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>

class IStream1 {

private:
int descriptor;
char buffer[4];
bool eof;

public:
IStream1();
void open(char *filename);
int read_next();
bool end_of_stream();

};
