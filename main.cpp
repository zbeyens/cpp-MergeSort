#include <io.h>
#include <iostream>
#include "istream/istream1.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    IStream1 reader1;
    reader1.open(argv[1]);

    while (!reader1.end_of_stream()) {
        int res = reader1.read_next();
        cout << res << endl;
    }

    return 0;
}
