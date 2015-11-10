#ifndef WORLD_H
#define WORLD_H

#define ALIVE 1
#define EMPTY 0

class World{

    private:
    	int width, heigth;
        unsigned short ** curr_world, ** new_world;
        int count_neigh(int row, int column);
        inline int mod(int a, int b);


    public:
    	World(int width, int heigth);
    	~World();
    	void print_world();
    	void randomize_world(int seed, int density);
    	void update_world();
    	void set_cell(int row, int column, int state);
};

#endif // WORLD_H