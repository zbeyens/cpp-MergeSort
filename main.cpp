#include <io.h>
#include <iostream>
#include "istream/istream2.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    IStream2 reader;
    FILE *ifile2 = reader.open(argv[1]);

    while (!reader.end_of_stream(ifile2)) {
        char res = reader.read_next(ifile2);
        cout << res;
    }

    cout << endl;

    return 0;
}
