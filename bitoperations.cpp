#include "bitoperations.h"

#define BIT_NUM 32
//for long int use #define BIT_NUM 64
//for short int use #define BIT_NUM 16

//BIT-ARRAY operations

void  SetBit( int A[ ],  int k )
{
	SET(A[k/BIT_NUM],(k%BIT_NUM)); // Set the bit at the k-th position in A[i]
}

void  ClearBit( int A[ ],  int k )                
{
    CLEAR(A[k/BIT_NUM],(k%BIT_NUM)); // RESET the bit at the k-th position in A[i]
}

int  TestBit( int A[ ],  int k )
{
	return (TEST(A[k/32],(k%32)) != 0 ); // Test the bit at the k-th position in A[i]     
}