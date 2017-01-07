#include "ostream4.h"
#include <cstdlib>
#include <cmath>
#include <io.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Producing files...";

    int nfile = 1;

    while (nfile <= 30) {
        OStream4 writer;
        string file_1 = to_string(nfile) + ".bin";

        writer.create(const_cast<char *>(file_1.c_str()) );
        int counter = 0;

        int limit = pow(10, 8); //38.1MB

        vector<int> res;

        while (counter < limit) {
            res.push_back(rand() % limit);
            counter++;
        }
        writer.write(res);

        cout << "DONE!" << endl;

        writer.close();
        nfile++;
    }



    return 0;
}
