#include "Barrier.h"

using namespace std;

#ifdef DEBUG
    #define debug_print(X) cout<<__FUNCTION__<< ": "<< (X) <<endl
#else
    #define debug_print(X)      
#endif

int workers, completed_workers = 0;

void inline Barrier::swap(){
    temp = *world;
    *world = *next;
    *next = temp;
}

void Barrier::join_barrier(){
    std::unique_lock<std::mutex> lock(m);
    completed_workers++;
    // debug_print(completed_workers);
    if(completed_workers == workers){
        completed_workers = 0;
        // debug_print("Barrier unlocked.");
        swap();
        cv.notify_all();
    }
    else
        cv.wait(lock);
}

void Barrier::set_workers(int nw){
    workers = nw;
}

void Barrier::set_worlds(unsigned short ***world, unsigned short ***next){
    this->world = world;
    this->next = next;
}
