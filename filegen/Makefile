CFLAGS=-Wall

LIBS = -lboost_iostreams

all: ostream2.o
	g++ ostream2.o filegen.cpp $(LIBS) -o filegen -std=c++11

ostream2.o: ostream2.cpp
	g++ -c ostream2.cpp -o ostream2.o

clean:
	rm ostream2.o

default: filegen

run:
	filegen $(ARGS)
