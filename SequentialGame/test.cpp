#include <iostream>
#include <thread>
#include <vector>

using namespace std;

inline int mod(int a, int b){
	return ( (a %= b) < 0 ) ? a + b : a;
}


int main(int argc, char * argv[]) {

	int width = 10, heigth = 10, row = 3, column = 3;

	int count = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if(i != 0 || j != 0){
				cout << mod(row+i, heigth) << " " << mod( column+j,width) << endl;
				//count += curr_world[mod(row+i, heigth)][mod(column+j,width)];
			}
		}
	}
	return(0); 
}
