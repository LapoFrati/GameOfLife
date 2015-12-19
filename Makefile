CC = g++
CFLAGS = -Wall -pedantic -std=c++0x
LDFLAGS = -pthread

.PHONY: clean debug $(FORCE) 

.DEFAULT: GameOfLife

GameOfLife: Main.cpp World.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

clean:
	-rm -f *.o GameOfLife test debug

run: GameOfLife
	./GameOfLife

test: test.cpp
	$(CC) $(CFLAGS) -o $@ $<
	./test

debug: CFLAGS += -DDEBUG -g
debug: clean GameOfLife
	-rm *.o
	mv GameOfLife debug
	./debug
