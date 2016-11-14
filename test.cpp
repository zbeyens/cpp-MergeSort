#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/iostreams/device/mapped_file.hpp> // for mmap
using namespace std;

int main() {
    boost::iostreams::mapped_file mmap("input.txt", boost::iostreams::mapped_file::readonly);

    //get the pointer to the first byte
    auto f = mmap.const_data();
    //get the size in bytes of the mapping
    auto l = f + mmap.size() + 1;

    while (f && f < l) {
        char buffer[4];

        for (size_t i = 0; i < 4; i++) {
            buffer[i] = *(f + i);
        }

        cout << *((int *)buffer) << endl;
        f += 4;
    }

    return 0;
}
