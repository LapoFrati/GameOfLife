#include "World.h"

using namespace std;

Barrier barrier;
int width, heigth;
unsigned short ** curr_world, ** new_world;

inline int mod(int a, int b){
	return ( (a %= b) < 0 ) ? a + b : a;
}

int count_neigh(unsigned short ** world, int row, int column){
	int count = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if(i != 0 || j != 0){
				if(world[mod(row+i, heigth)][mod(column+j,width)] == ALIVE)
					count += 1;
			}
		}
	}
	return count;
}

void body(int start_row, int end_row, int columns, int iterations){
	int count;
	
	#ifdef DEBUG
		cout << "Received from "<< start_row << " to " << end_row<< " load: "<< end_row - start_row << endl;
	#endif

	for (int k = 0; k < iterations; ++k)
	{
		for (int i = start_row; i < end_row; ++i)
		{	for (int j = 0; j < columns; ++j)
			{	count = count_neigh(curr_world,i,j);
				switch(curr_world[i][j]){
						case ALIVE:	if(count == 2 || count == 3)
										new_world[i][j] = ALIVE;
									else /* count < 2 || count > 3 */
										new_world[i][j] = EMPTY;
									break;

						case EMPTY: if (count == 3)
										new_world[i][j] = ALIVE;
									else
										new_world[i][j] = EMPTY;
									break;
					}
			}
		}

		barrier.join_barrier();
	}
}


World::World(int w, int h, int workers){
	width = w;
	heigth = h;

	nw = (workers > heigth) ? heigth : workers; // limit nw by number of rows

	barrier.set_workers(nw); 
	
	chunk = heigth / nw;
	more = heigth % nw;
	
	#ifdef DEBUG
		cout << "chunk: " << chunk <<" more: " << more << endl;
	#endif

	curr_world = new unsigned short*[heigth];
	new_world = new unsigned short*[heigth];
	for (int i = 0; i < heigth; ++i)
	{	
		curr_world[i] = new unsigned short [width];
		new_world[i] = new unsigned short [width];
	}

	barrier.set_worlds(&curr_world, &new_world);

	for (int i = 0; i < heigth; ++i)
		for (int j = 0; j < width; ++j)
			curr_world[i][j] = EMPTY;
}

World::~World(){
	for (int i = 0; i < heigth; ++i)
	{
		delete curr_world[i];
		delete new_world[i];
	}

	delete[] curr_world;
	delete[] new_world;
}

void World::print_world(){
	cout <<"  ";
	for (int j = 0; j < width; ++j)
		cout << j << " ";
	cout << endl;
	for (int i = 0; i < heigth; ++i)
	{	cout << i<<"|";
		for (int j = 0; j < width; ++j)
		{	if( j == width-1)
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

	#ifdef DEBUG
		cout<<"Debug: Count of Neighbours"<<endl;
		for (int i = 0; i < heigth; ++i)
		{	cout << i << "|";
			for (int j = 0; j < width; ++j)
				cout << count_neigh(curr_world,i,j) << " ";
			cout << endl;
		}
	#endif
}

void World::randomize_world(int seed, int density){
	srand(seed);

	for (int i = 0; i < heigth; ++i)
		for (int j = 0; j < width; ++j)
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
		tid.push_back(std::thread(body, start, stop, width, iterations)); 
  	}

	for(int i=0; i<nw; i++) 
		tid[i].join();
}

void World::set_cell(int row, int column, int state){
	if(state == ALIVE || state == EMPTY)
		curr_world[row][column] = state;
}