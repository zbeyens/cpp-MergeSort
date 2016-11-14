#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

class OStream13 {
private:
int ofile13;

public:
OStream13();

void create(char *filename);
void write(std::vector<int> elem);
void close();
};
