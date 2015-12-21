#include "World.h"


using namespace std;

Barrier barrier;
int width, height;
unsigned short ** curr_world, ** new_world;

void body(int start_row, int end_row, int columns, int iterations){

#ifdef DEBUG
    cout << start_row << " to " << end_row << endl;
#endif

    for (int k = 0; k < iterations; ++k)
    {
        for (int i = start_row; i < end_row; ++i)
        {
          #define COUNT(i,j) ( curr_world[i-1][j-1] + curr_world[i-1][ j ] + curr_world[i-1][j+1] \
                             + curr_world[ i ][j-1]                        + curr_world[ i ][j+1] \
                             + curr_world[i+1][j-1] + curr_world[i+1][ j ] + curr_world[i+1][j+1] )
           // #pragma vector always
            for (int j = 1; j < columns+1; ++j)
            {
                new_world[i][j] = (curr_world[i][j] == 0)*(COUNT(i,j)==3) + (curr_world[i][j] == 1)*((COUNT(i,j)>=2)&&(COUNT(i,j)<=3));

                // update padding
                //
                // 0: OxxxO
                // 1: x---x
                // 2: x---x
                // 3: OxxxO
                //
                //steps:
                // copy 1 -> 3
                // copy 2 -> 0
                // compute corners
                // update first column and last column
                //
            }
                if( i == 1 ){
                    new_world[height+1]            = new_world[1]; // computed first row, copy to the bottom
                    new_world[height+1][0]         = new_world[1][columns]; // copy the corners to complete the torus
                    new_world[height+1][columns+1] = new_world[1][1]; // copy the corners to complete the torus
                }
                if( i == height ){
                    new_world[0]            = new_world[height]; // computed last row, copy to the top
                    new_world[0][0]         = new_world[height][columns]; // copy the corners to complete the torus
                    new_world[0][columns+1] = new_world[height][1]; // copy the corners to complete the torus
                }
                if ( i != 1 && i != height ){ // update first and last columns
                    new_world[i][0]         = new_world[i][columns];
                    new_world[i][columns+1] = new_world[i][1];
                }

            }

        barrier.join_barrier();
    }
}


World::World(int w, int h, int workers){
    width = w;
    height = h;

    nw = (workers > height) ? height : workers; // limit nw by number of rows

    barrier.set_workers(nw);

    chunk = height / nw;
    more = height % nw;

#ifdef DEBUG
    cout << "chunk: " << chunk <<" more: " << more << endl;
#endif
    curr_world = new unsigned short*[height+2];
    new_world = new unsigned short*[height+2];
    for (int i = 0; i < height+2; ++i)
    {
        curr_world[i] = new unsigned short [width+2];
        new_world[i] = new unsigned short [width+2];
    }

    barrier.set_worlds(&curr_world, &new_world);

    for (int i = 0; i < height+2; ++i)
        for (int j = 0; j < width+2; ++j)
            curr_world[i][j] = EMPTY;
}

void World::print_world(){
    cout <<"  ";
    for (int j = 0; j < width+2; ++j)
        cout << (j) << " ";
    cout << endl;
    for (int i = 0; i < height+2; ++i)
    {	cout << (i) <<"|";
        for (int j = 0; j < width+2; ++j)
        {	if( j == width+1)
            if(curr_world[i][j] == ALIVE)
                cout <<"O";
            else
                cout <<" ";
            else
                if(curr_world[i][j] == ALIVE)
                    cout <<"O ";
                else
                    cout <<"  ";
        }
        cout << "|" <<endl;
    }
}

void World::randomize_world(int seed, int density){
    srand(seed);

    for (int i = 1; i < height+1; ++i)
        for (int j = 1; j < width+1; ++j)
            if( (rand()%density) == 0)
                curr_world[i][j] = ALIVE;
            else
                curr_world[i][j] = EMPTY;
}

void World::update_world(int iterations){
    std::vector<std::thread> tid;
    int start = 0, stop = 0, excess = more;

    for(int i=0; i<nw; i++) {
        start = stop;
        stop  = start + chunk + (excess-- > 0 ? 1 : 0);
        tid.push_back(std::thread(body, (start+1), (stop+1), width, iterations));
    }

    for(int i=0; i<nw; i++)
        tid[i].join();
}

void World::set_cell(int row, int column, int state){
    if(state == ALIVE || state == EMPTY)
        curr_world[row][column] = state;
}
