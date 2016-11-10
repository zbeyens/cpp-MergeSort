CFLAGS=-Wall
11=istream/istream1
21=istream/istream2
22=ostream/ostream2

all: $(11).o $(21).o $(22).o
	g++ $(11).o $(21).o $(22).o main.cpp -o main -std=c++11

$(11).o: $(11).cpp
	g++ -c $(11).cpp -o $(11).o

$(21).o: $(21).cpp
	g++ -c $(21).cpp -o $(21).o

$(22).o: $(22).cpp
	g++ -c $(22).cpp -o $(22).o

clean:
	rm *.o

default: main

run:
	main $(ARGS)
