#include <io.h>
#include <iostream>
#include "istream/istream2.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    IStream2 reader2;
    reader2.open(argv[1]);

    while (!reader2.end_of_stream()) {
        int res = reader2.read_next();
        cout << res << endl;
    }

    cout << endl;

    return 0;
}
