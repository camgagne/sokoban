CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

all: Sokoban.a Sokoban test

Sokoban: main.o Sokoban.o
	$(CC) $(CFLAGS) -o Sokoban main.o Sokoban.o $(LIB)

test: test.o Sokoban.o
	$(CC) $(CFLAGS) -o test test.o Sokoban.o $(LIB)

Sokoban.a: Sokoban.o
	ar rcs Sokoban.a Sokoban.o

main.o: main.cpp Sokoban.hpp
	$(CC) $(CFLAGS) -c main.cpp

Sokoban.o: Sokoban.cpp Sokoban.hpp
	$(CC) $(CFLAGS) -c Sokoban.cpp

test.o: test.cpp Sokoban.hpp
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm -f Sokoban test test.o main.o Sokoban.o Sokoban.a

lint:
	cpplint *.cpp *.hpp
