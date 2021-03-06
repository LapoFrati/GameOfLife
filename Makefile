CC = g++
CFLAGS = -Wall -pedantic -std=c++0x
LDFLAGS = -pthread

.PHONY: clean debug intel

.DEFAULT: GameOfLife

GameOfLife: Main.cpp World.o Barrier.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

clean:
	-rm -f *.o GameOfLife test debug

intel : CFLAGS += -O3 -ipo -xHost
intel : CC = icpc
intel : GameOfLife

test: test.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
	./test

debug: CFLAGS += -DDEBUG -g
debug: clean GameOfLife
	-rm *.o
	mv GameOfLife debug
	./debug
