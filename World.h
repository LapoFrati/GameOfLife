#ifndef WORLD_H
#define WORLD_H

#include "Barrier.h"
#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>

#define ALIVE 1
#define EMPTY 0

class World{
	private:
		unsigned short ** curr_world, ** new_world;
		int nw, availableConcurrentThreads, chunk;

    public:
    	World(int w, int h);
    	~World();
    	void print_world();
    	void randomize_world(int seed, int density);
    	void update_world(int iterations);
    	void set_cell(int row, int column, int state);
        
};

#endif // WORLD_H