CFLAGS = -Wall -Werror -g -std=c++14
PROJ = program3

all: Planet.o Galaxy.o program3

program3: program3.o
	g++ $(CLFAGS) $(PROJ).o Galaxy.o Planet.o -o $(PROJ)

program3.o: program3.cpp Planet.h Galaxy.h
	g++ $(CFLAGS) -c $(PROJ).cpp -o $(PROJ).o 

Galaxy.o: Galaxy.cpp
	g++ $(CFLAGS) -c Galaxy.cpp -o Galaxy.o

Planet.o: Planet.cpp
	g++ $(CFLAGS) -c Planet.cpp -o Planet.o




.PHONY: clean run

clean:
	rm *.o
	rm $(PROJ)

run: all
	./$(PROJ)

memcheck: all
	valgrind -v ./$(PROJ)
