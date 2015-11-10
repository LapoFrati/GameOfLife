#include <iostream>
#include <thread>
#include <vector>
#include "World.h"

#define ITERATIONS	1
using namespace std;

int main(int argc, char * argv[]) {

	// number of threads to be used
	//int retval,i,nw = atoi(argv[1]);
	//std::vector<std::thread> tid; 

	World world(10,10);
	//world.randomize_world(42, 3);
	/* GLIDER */
	world.set_cell(1, 2, ALIVE);
	world.set_cell(2, 3, ALIVE);
	world.set_cell(3, 1, ALIVE);
	world.set_cell(3, 2, ALIVE);
	world.set_cell(3, 3, ALIVE);
	/**/

	world.print_world();
	world.update_world(ITERATIONS);
	world.print_world();

	return(0); 
}
