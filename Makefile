CFLAGS=-Wall
11=istream/istream13
12=ostream/ostream13
21=istream/istream2
22=ostream/ostream2
41=istream/istream4
dep=$(11).o $(12).o $(21).o $(22).o $(41).o

LIBS = -lboost_iostreams

all: $(dep)
	g++ $(dep) main.cpp $(LIBS) -o main -std=c++11

$(11).o: $(11).cpp
	g++ -c $(11).cpp -o $(11).o

$(12).o: $(12).cpp
	g++ -c $(12).cpp -o $(12).o

$(21).o: $(21).cpp
	g++ -c $(21).cpp -o $(21).o

$(22).o: $(22).cpp
	g++ -c $(22).cpp -o $(22).o

$(41).o: $(41).cpp
	g++ -c $(41).cpp -o $(41).o

default: main

run:
	main $(ARGS)

clean:
	rm $(dep)
