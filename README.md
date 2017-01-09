# mergesort
Algorithms in Secondary Memory.

Run the Makefile.

Example of arguments:

For part 1 (method 1): 1 10000 3 0 5

For part 1 (method 2): 2 10000 3 0 5

For part 1 (method 3): 3 10 3 0 5

For part 1 (method 4): 4 10 3 0 5

For part 3: 5 10 3 0 5 10 2 input.bin

##param 1: method
Part 1: method 1 to 4. For part 3: method 5.

##param 2: k (max 30)
Part 1: the number of streams (on distinct files) to open.

##param 3: repeat
Number of times to repeat, to average the time cost

##param 4: N
Part 1: Number of int to read (for method 1 and 2). If N=0, we take the entire file.

##param 5: factorB
Size of the buffer for method 3 and 4

##param 6: M
Part 3: Size of the main memory available (first sort phase)

##param 7: d
Part 3: the number of streams to merge in one pass (in the later sort phases)

##param 8: file input
Part 3: the string file input
