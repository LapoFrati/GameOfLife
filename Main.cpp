#include <stdio.h>
#include <iostream>
#include <bitset>
#include <stdint.h>
#include <inttypes.h>
#include "bitoperations.h"

using namespace std;

#define OUTER_ROW 0x0007
#define INNER_ROW 0x0005
#define CENTER    0x0002

// static const unsigned char BitsSetTable256[256] =
// {
// #   define B2(n) n,     n+1,     n+1,     n+2
// #   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
// #   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
//     B6(0), B6(1), B6(1), B6(2)
// };

static const unsigned char BitsSetTable512[512] =
{
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
#   define B8(n) B6(n), B6(n+1), B6(n+1), B6(n+2)
    B8(0), B8(1)
};

void printBinary (int a){
    int temp;
    for (int i = 0; i < 32; ++i) {
        if( (i % 8) == 0)
            cout << " | ";
        temp = (a & (1 << (31 - i))) >> (31 - i);
        if(temp == 0)
            cout << "  ";
        else
            cout << "o ";
    }
    cout << "|" << endl;
}

// unsigned int BitsSetTable512[512];
// void initializeBitsSetTable512(){
//
//     BitsSetTable512[0] = 0;
//     for (int i = 0; i < 512; i++)
//     {
//         BitsSetTable512[i] = (i & 1) + BitsSetTable512[i / 2];
//     if(BitsSetTable[j] != BitsSetTable512[j])
//       cout << j << ": "<< BitsSetTable[j] << " vs " << BitsSetTable512[j] << endl;
//     }
// }

void setBit( uint32_t *a, int pos){
    *a = *a | 1 << pos;
}

int main(void){
    // int A[10];
    // int i;

    uint32_t world[32], new_world[32];
    unsigned short int center, tot;
                   // newState, temp_a=0, temp_b=0, temp_c=0;

    for (int i = 0; i < 32; ++i) {
       world[i]=0;
       new_world[i]=0;
    }

    setBit(&world[1], 11);
    setBit(&world[2], 10);
    setBit(&world[3], 10);
    setBit(&world[3], 11);
    setBit(&world[3], 12);

    printBinary(world[0]);
    printBinary(world[1]);
    printBinary(world[2]);
    printBinary(world[3]);
    printBinary(world[4]);

    // for (int i = 0; i < 32 - 3 #<{(| type width - mask size |)}>#; ++i) {
    //     temp_a = BitsSetTable512[ (world[1] >> i ) & OUTER_ROW ];
    //     temp_b = BitsSetTable512[ (world[2] >> i ) & INNER_ROW ];
    //     temp_c = BitsSetTable512[ (world[3] >> i ) & OUTER_ROW ];
    //     center = BitsSetTable512[ (world[2] >> i ) & CENTER    ];
    //     tot    = BitsSetTable512[ ((( world[1] >> i ) & OUTER_ROW) << 6 ) | ((( world[2] >> i ) & INNER_ROW) << 3 ) | (( world[3] >> i ) & OUTER_ROW) ];
    //     newState = (center == 0) * (tot == 3) + (center == 1) * ((tot >= 2) && (tot <= 3));
    //     cout << "a: " << temp_a << " b: " << temp_b << " c: " << temp_c << " State: " << center << " Tot: " << tot << " new: " << newState << endl;
    // }

    for (int k = 0; k < 4/* 32 - 3 */; ++k){
        new_world[k+1] = 0;
        for (int i = 0; i < 32 - 3 /* type width - mask size */; ++i) {
            tot = BitsSetTable512[((( world[k]   >> i ) & OUTER_ROW) << 6 )
                                 |((( world[k+1] >> i ) & INNER_ROW) << 3 )
                                 |((  world[k+2] >> i ) & OUTER_ROW) ];
            center = BitsSetTable512[ (world[k+1] >> i ) & CENTER    ];
            new_world[k+1] |= ((center == 0) * (tot == 3) + (center == 1) * ((tot >= 2) && (tot <= 3))) << i;
            // cout << tot;
        }
    }

    printBinary(new_world[0]);
    printBinary(new_world[1]);
    printBinary(new_world[2]);
    printBinary(new_world[3]);
    printBinary(new_world[4]);

}
