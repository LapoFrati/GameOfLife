
#define SET(X,N) 	((X) |=  (1 << (N)))
#define CLEAR(X,N) 	((X) &= ~(1 << (N)))
#define SWITCH(X,N) ((X) ^=  (1 << (N)))
#define TEST(X,N)	((X)  &  (1 << (N)))
#define FLIP(X)		((X)  = ~(X))
#define COUNT1(X)	(__builtin_popcount(X))

//BIT-ARRAY operations

void  SetBit( int A[ ],  int k ); // Set the bit at the k-th position in A[i]

void  ClearBit( int A[ ],  int k ); // RESET the bit at the k-th position in A[i]

int  TestBit( int A[ ],  int k ); // Test the bit at the k-th position in A[i]     
