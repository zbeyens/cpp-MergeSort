#include "ostream2.h"
#include <cstdlib>
#include <io.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Producing files...";
    OStream2 writer;
    string file_1 = "random.bin";

    writer.create(const_cast<char *>(file_1.c_str()) );
    int counter = 0;

    while (counter < 20000) {
        writer.write(rand() % 20000);
        counter++;
    }

    cout << "DONE!" << endl;

    writer.close();


    return 0;
}
