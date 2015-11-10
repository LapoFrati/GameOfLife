#ifndef BARRIER_H
#define BARRIER_H

#include <mutex>
#include <condition_variable>
#include <iostream>

class Barrier{

    private:
        std::mutex m;
        std::condition_variable cv;
        unsigned short *** world, ***next, **temp;
        
    public:
        void join_barrier();
        void set_workers(int nw);
        void set_worlds(unsigned short ***world, unsigned short ***next);
        void inline swap();
};

#endif // BARRIER_H