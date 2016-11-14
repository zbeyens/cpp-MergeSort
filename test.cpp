#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/iostreams/device/mapped_file.hpp> // for mmap
using namespace std;

int main() {
    boost::iostreams::mapped_file mmap("input.txt", boost::iostreams::mapped_file::readonly);

    //get the pointer to the first byte, const for readyonly
    const char *ifile = mmap.const_data();
    //get the size in bytes of the mapping
    const char *length = ifile + mmap.size();

    while (ifile && length - ifile >= 4) {
        char buffer[4];

        for (size_t i = 0; i < 4; i++) {
            buffer[i] = *(ifile + i);
        }

        cout << *((int *)buffer) << endl;
        ifile += 4;
    }

    return 0;
}
