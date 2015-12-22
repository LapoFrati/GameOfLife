#include <iostream>
#include <thread>
#include <vector>

#define ALIVE 1
#define EMPTY 0

using namespace std;

std::vector<std::thread> tid;
unsigned short **new_world,** curr_world;
int width = 10, height = 10;

inline int mod(int a, int b){
    return ( (a %= b) < 0 ) ? a + b : a;
}

void body(int start_row, int end_row,int columns){
    int count = 0;
    cout << "Received: "<< start_row << "-"<<end_row<<endl;
    for (int i = start_row; i <= end_row; ++i)
    {
        for (int j = 1; j < columns - 1; ++j)
        {
                count = ( curr_world[i-1][j-1] + curr_world[i-1][ j ] + curr_world[i-1][j+1]
                        + curr_world[ i ][j-1]                        + curr_world[ i ][j+1]
                        + curr_world[i+1][j-1] + curr_world[i+1][ j ] + curr_world[i+1][j+1] );
                new_world[i][j] = (curr_world[i][j] == 0)*(count==3) + (curr_world[i][j] == 1)*((count>=2)&&(count<=3));
        }
    }
}

void print_world(){
    cout <<"  ";
    for (int j = 0; j < width; ++j)
        cout << j << " ";
    cout << endl;
    for (int i = 0; i < height; ++i)
    {   cout << i<<"|";
        for (int j = 0; j < width; ++j)
        {   if( j == width-1)
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


int main() {

    int chunk;
    int nw = 2;

    chunk = height / nw;

    curr_world = new unsigned short*[height+2];
    new_world = new unsigned short*[height+2];

    for (int i = 0; i < height+2; ++i)
    {
        curr_world[i] = new unsigned short [width+2];
        new_world[i] = new unsigned short [width+2];
    }

    for (int i = 0; i < height+2; ++i)
        for (int j = 0; j < width+2; ++j)
            curr_world[i][j] = EMPTY;

    for(int i=0; i<nw; i++) {

        if( i == 0 )
            tid.push_back(std::thread(body, 0 , chunk*(i+1)-1, width));
        else
            if( i == nw-1)
                tid.push_back(std::thread(body, chunk*i, height-1, width));
            else
                tid.push_back(std::thread(body, (chunk*i), chunk*(i+1)-1, width));
    }

for(int i=0; i<nw; i++)
    tid[i].join();

print_world();

    return(0);
}


