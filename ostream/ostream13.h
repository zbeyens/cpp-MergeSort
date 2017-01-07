#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>

class OStream13 {
private:
int ofile13;
char *file_name;

public:
OStream13();

void create(char *filename);
void write(std::vector<int> elem);
void close();
char * get_filename();
void free();
};
