#include "World.h"
#include <iostream>

using namespace std;

World::World(int width, int heigth): width(width), heigth(heigth){

	// curr_world = (unsigned short**) malloc ( heigth*sizeof(short*));
	// new_world = (unsigned short**) malloc ( heigth*sizeof(short*));
	curr_world = new unsigned short*[heigth];
	new_world = new unsigned short*[heigth];
	for (int i = 0; i < heigth; ++i)
	{
		// curr_world[i] = (unsigned short*)malloc( width*sizeof(short));
		// new_world[i] = (unsigned short*)malloc( width*sizeof(short));
		curr_world[i] = new unsigned short [width];
		new_world[i] = new unsigned short [width];
	}

	for (int i = 0; i < heigth; ++i)
		for (int j = 0; j < width; ++j)
			curr_world[i][j] = EMPTY;
}

World::~World(){
	//std::cout <<"Deleting"<<std::endl;
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
}

void World::randomize_world(int seed, int density){
	srand(seed);

	for (int i = 0; i < heigth; ++i)
		for (int j = 0; j < width; ++j)
			if( (rand()%density) == 0)
				curr_world[i][j] = 1;
			else
				curr_world[i][j] = 0;
		
}

void World::update_world(){
	int count = 0;
	unsigned short** tmp;

	for (int i = 0; i < heigth; ++i)
	{	for (int j = 0; j < width; ++j)
		{	count = count_neigh(i,j);
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

	#ifdef DEBUG
		cout<<"Debug: Count of Neighbours"<<endl;
		for (int i = 0; i < heigth; ++i)
		{	cout << i << "|";
			for (int j = 0; j < width; ++j)
				cout << count_neigh(i,j) << " ";
			cout << endl;
		}
	#endif

	/* swap worlds */
	tmp = curr_world;
	curr_world = new_world;
	new_world = tmp;
}

int World::count_neigh(int row, int column){
	int count = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if(i != 0 || j != 0){
				if(curr_world[mod(row+i, heigth)][mod(column+j,width)] == ALIVE)
					count += 1;
			}
		}
	}
	return count;
}

void World::set_cell(int row, int column, int state){
	if(state == ALIVE || state == EMPTY)
		curr_world[row][column] = state;
}

inline int World::mod(int a, int b){
	return ( (a %= b) < 0 ) ? a + b : a;
}