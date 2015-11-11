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
		
		int nw, chunk, more;

    public:
    	World(int w, int h, int workers);
    	~World();
    	void print_world();
    	void randomize_world(int seed, int density);
    	void update_world(int iterations);
    	void set_cell(int row, int column, int state);
        
};

#endif // WORLD_H