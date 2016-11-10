#include <io.h>
#include <iostream>
#include "istream/istream2.h"
#include "ostream/ostream2.h"
#include "istream/istream1.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 0;
    }

    cout << "First method" << endl;
    IStream1 reader1;
    reader1.open(argv[1]);

    while (!reader1.end_of_stream()) {
        int res = reader1.read_next();
        cout << res << endl;
    }

    cout << endl << "Second method" << endl;
    IStream2 reader2;
    OStream2 writer2;
    reader2.open(argv[1]);
    writer2.create(argv[2]);

    while (!reader2.end_of_stream()) {
        int res = reader2.read_next();
        writer2.write(res);
        cout << res << endl;
    }
    writer2.close();

    return 0;
}
