CFLAGS=-Wall
2=istream/istream2

all: $(2).o
	g++ $(2).o main.cpp -o main -std=c++11

$(2).o: $(2).cpp
	g++ -c $(2).cpp -o $(2).o

clean:
	rm *.o

default: main

run:
	main $(ARGS)
