#include <iostream>
#include <thread>
#include <vector>
#include "World.h"

using namespace std;

int main(int argc, char * argv[]) {

    if (argc < 4) {
        std::cerr << "use: " << argv[0]  << " dim iterations nworkers ?[print: on]\n";
        return -1;
    }

    int dim        = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    int workers    = atoi(argv[3]);
    int print      = 0;

    if (argc >= 5) print = (std::string(argv[4]) == "on");

    World world(dim, dim, workers);
    //world.randomize_world(42, 3);

    /* GLIDER */
    world.set_cell(1, 2, ALIVE);
    world.set_cell(2, 3, ALIVE);
    world.set_cell(3, 1, ALIVE);
    world.set_cell(3, 2, ALIVE);
    world.set_cell(3, 3, ALIVE);

    if(print)
        world.print_world();
    world.update_world(iterations);
    if(print)
        world.print_world();
    return(0);
}
