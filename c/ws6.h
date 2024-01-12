#ifndef __WS6_H__
#define __WS6_H__



/* return bitwise x*(2^y) */
long Pow2(unsigned int x, unsigned int y);

/* returns 1 if n is a product of 2^something */
int IsPowTwoLoop(unsigned int n);

/* returns 1 if n is a product of 2^something implemented without loop*/
int IsPowTwo(unsigned int n);

/* Adds 1 and returns n + 1 using bitwise operators */
int AddOne(int n);

/* returns the bitwise mirror of n using loop */
unsigned char ByteMirror(unsigned char n);

/* return the bitwise mirror of n  */
unsigned char ByteMirrorNoLoop(unsigned char c);

/* swaps x and y */
int SwapWithoutTemp(unsigned int *x, unsigned int *y);

/* return 1 if bits 6 and 2 are set ( == 1 ) */
int CheckSixTwo(unsigned char c);

/* return 1 if bits 6 OR 2 are set */
int CheckSixOrTwo(unsigned char c);

/* return the number of set bits in n */
int CountSetBits(unsigned int n);

/* return the number of set bits in b - using recursion */
int CountSetBitsNoLoop(unsigned int n);

/* returns the closest num divisble by 16 */
unsigned int ClosestNumDivBy16(unsigned int n);

/* prints if the number has 3 set bits for every element in arr[size] */
void ThreeBitSet(int arr[], int size);

/* prints float number in binary representation */
void PrintFloatToBinary(float n);



#endif /* __WS6_H__ */
