CFLAGS=-Wall
1=istream/istream1
2=istream/istream2

all: $(1).o $(2).o
	g++ $(1).o $(2).o main.cpp -o main -std=c++11

$(1).o: $(1).cpp
	g++ -c $(1).cpp -o $(1).o

$(2).o: $(2).cpp
	g++ -c $(2).cpp -o $(2).o

clean:
	rm *.o

default: main

run:
	main $(ARGS)
