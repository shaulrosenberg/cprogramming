#include <stdio.h>/* printf */
#include <math.h> /* pow    */
#include "ws6.h"


/* every left shift is like we multiplied the expression by 2 
*  so x << 1 = x * 2
*     x << 2 = x * 2 * 2
*	  x << y = x * 2^y	
*	  Ex1
*/
long Pow2(unsigned int x, unsigned int y)
{
	return x<<y; 
}

/* Ex2 - n & (n-1) returns all zero's if the number is product of pow2, */
int IsPowTwo(unsigned int n)
{
	return !(n & (n - 1)) ? 1 : 0;
}


/* loop through all the set bits, add to count if set bit, shift right to discard, repeat untill n  */
int IsPowTwoLoop(unsigned int n)
{	
	unsigned int count = 0;
	while(n)
	{
		count += n & 1;
		n >>= 1;
	}
	if(count != 1) return 0; /* only 1 bit set for pow2 numbers */
	
	return 1; /* true */
}

/* Ex3 
*  first we iterate m & n to find where to place our carries only 1 & 1 will produce a carry, 
*  but, we want to apply our carry to the left and not at the current spot.
*  
*  
*/
int AddOne(int n)
{
	int m = 1;
	while(m & n)
	{
		n = n ^ m;
		m <<= 1;
	}
	n = n ^ m;
	
	return n;
}


/* Ex5 - keep shifting n to the right while "copying" every bit from n into result */

unsigned char ByteMirror(unsigned char n)
{
	unsigned char i = 0, result = 0;
	for (i = 0; i < 8; ++i)
	{
		result = ((result << 1) | (n & 1));
		n = n >> 1;
	}
	
	return result;
}

unsigned char ByteMirrorNoLoop(unsigned char c)
{
	c = (((c & 240) >> 4) | ((c & 15) << 4));             /*change nibble 240 = 1111 0000 , 15 = 0000 1111*/                
	c = (((c & 204) >> 2) | ((c & 51) << 2)); 			 /*change tuple 11001100 | 00110011*/
	c = (((c & 170) >> 1) | ((c & 85) << 1)); 			/*change bits 10101010 | 01010101*/
				
	return c;
}


/* Ex8
*  x = x ^ y   - this represents 
*  y = x ^ y ^ y = x 
*  x = x ^ y 
*/
int SwapWithoutTemp(unsigned int *x, unsigned int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
	printf("x = %d, y = %d", *x, *y);
	
	return 0;
}


/* Ex6 - Idea: Mask k-1 (6 -> 5 2-> 1) bits, check if they are set using & for */
int CheckSixTwo(unsigned char c)
{
	 return (c & (1 << 1)) && (c & (1 << 5));
}

int CheckSixOrTwo(unsigned char c)
{
	return (c & (1 << 1)) || (c & (1 << 5));	
}

int SwapThirdAndFifthBit(unsigned int n)
{
	
	int mask3 = 4;     				   /* 00000100 */
	int mask5 = 16;    				   /* 00010000 */
	int not_mask35 = ~(mask3 | mask5); /* 11101011 */
	mask5 = (mask5 & n) >> 2;		   /* shift the 5th bit in n to 3rd place */
	mask3 = (mask3 & n) << 2;		   /* shift the 3rd bit in n to 5th place */
	n = n & not_mask35; 			   /* reset 5 and 3 bit */
	n = n | mask5;					   /* */
	n = n | mask3;

	return n;
}

/* Ex9 similar to ex2 loop */
int CountSetBits(unsigned int n)
{
	int count = 0;
	while(n)
	{
		count += n & 1;
		n >>= 1;
	}
	
	return count;
}
/*  Ex9 using recursion */
int CountSetBitsNoLoop(unsigned int n)
{
	/* base */
	int count = 0;
	if(n == 0) return 0;

	return CountSetBitsNoLoop(n >> 1) + 1;
}

/* Ex7 */

unsigned int ClosestNumDivBy16(unsigned int n)
{
	unsigned int mask = 15; /* 00001111 */
	unsigned int res = 0;
	res = (~mask) & n;		/* res = 11110000 & n */
	
	return res;
}


/* Ex4  - using our bit counting functions */
void ThreeBitSet(int arr[], int size)
{
	int i = 0;
	for(i = 0; i < size; ++i)
	{
		if(CountSetBits(arr[i]) == 3)
		{
			printf("%d has 3 bits set\n", arr[i]);
		}
	}
}

/* Print a floating number's binary representation  */
void PrintFloatToBinary(float n)
{
	unsigned int *ptr_f = (unsigned int *) & n;
    unsigned int mask = ((unsigned int) pow(2, 31)); /* turn on last bit - we keep printing the last bit and shifting it */
	int i = 0;

	for( i = 0; i <= 31; ++i)
	{
		printf("%d", (*ptr_f & mask) >> (31-i));
		mask >>= 1;
	}
	printf("\n");
}







