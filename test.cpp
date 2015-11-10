#include <iostream>
#include <thread>
#include <vector>

#define ALIVE 1
#define EMPTY 0

using namespace std;

std::vector<std::thread> tid;
unsigned short **world;
int width = 10, heigth = 10;

inline int mod(int a, int b){
	return ( (a %= b) < 0 ) ? a + b : a;
}

void body(int start_row, int end_row,int columns){
	cout << "Received: "<< start_row << "-"<<end_row<<endl;
	for (int i = start_row; i <= end_row; ++i)
	{
		world[i] = new unsigned short [width];
		for (int j = 0; j < width; ++j)
			world[i][j] = ALIVE;
	}
}

void print_world(){
	cout <<"  ";
	for (int j = 0; j < width; ++j)
		cout << j << " ";
	cout << endl;
	for (int i = 0; i < heigth; ++i)
	{	cout << i<<"|";
		for (int j = 0; j < width; ++j)
		{	if( j == width-1)
				if(world[i][j] == ALIVE)
					cout <<"O";
				else
					cout <<" ";
			else
				if(world[i][j] == ALIVE)
					cout <<"O ";
				else
					cout <<"  ";
		}
		cout << "|" <<endl;
	}
}


int main(int argc, char * argv[]) {

	int chunk;
	int availableConcurrentTrheads = std::thread::hardware_concurrency();
	int nw = availableConcurrentTrheads % heigth; // limit nw by number of rows

	chunk = heigth / nw;

	world = new unsigned short*[heigth];

	for(int i=0; i<nw; i++) {

		if( i == 0 )
			tid.push_back(std::thread(body, 0 , chunk*(i+1)-1, width));
		else
			if( i == nw-1)
				tid.push_back(std::thread(body, chunk*i, heigth-1, width)); 
			else
				tid.push_back(std::thread(body, (chunk*i), chunk*(i+1)-1, width));
  	}

for(int i=0; i<nw; i++) 
	tid[i].join();

print_world();

	return(0); 
}


