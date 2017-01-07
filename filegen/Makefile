CFLAGS=-Wall

LIBS = -lboost_iostreams

all: ostream4.o
	g++ ostream4.o filegen.cpp $(LIBS) -o filegen -std=c++11

ostream4.o: ostream4.cpp
	g++ -c ostream4.cpp -o ostream4.o

clean:
	rm ostream4.o

default: filegen

run:
	filegen $(ARGS)
