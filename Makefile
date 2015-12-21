CC = g++
CFLAGS = -Wall -pedantic -std=c++0x
LDFLAGS = -pthread

.PHONY: clean debug intel run

.DEFAULT: GameOfLife

GameOfLife: Main.cpp World.o Barrier.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

clean:
	-rm -f *.o GameOfLife test debug

intel : CFLAGS += -O3 -ipo -xHost -vec-report
intel : CC = icpc
intel : GameOfLife

test: test.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
	./test

run: GameOfLife
	./GameOfLife 8 1 2 on

debug: CFLAGS += -DDEBUG -g
debug: clean GameOfLife
	-rm *.o
	mv GameOfLife debug
	./debug 8 1 2 on
