#include <stdio.h> /* size_t printf */
#include <string.h> /* strlen memset */
#include "bit_arr.h"

#define BIT_ARR_SIZE 64

/* helper function for Reverse */
static void Swap(char *c1, char *c2)
{
	char temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

/* helper function for ToString */
static void Reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        Swap((str+start), (str+end));
        start++;
        end--;
    }
}


bit_arr_ty BitArrSetAll(bit_arr_ty bit_array)
{
	return ~(bit_array & 0);
}


bit_arr_ty BitArrResetAll(bit_arr_ty bit_array)
{
	return (bit_array & 0);
}


bit_arr_ty BitArrSetOn(bit_arr_ty bit_array, size_t index)
{
	bit_array = bit_array | 1 << index;
	return bit_array;
}

bit_arr_ty BitArrSetOff(bit_arr_ty bit_array, size_t index)
{
	bit_array = bit_array & ~(1 << index);
	return bit_array;
}

bit_arr_ty BitArrSetBit(bit_arr_ty bit_array, size_t index, unsigned int bool_val)
{
	bit_array = (size_t)bool_val << index | BitArrSetOff(bit_array, index);
	return bit_array;
}

unsigned int BitArrGetVal(bit_arr_ty bit_array, size_t index)
{
	/* shift val to beginning of bit_array & 1 */
	return (bit_array >> index) & 1;
}

bit_arr_ty BitArrFlip(bit_arr_ty bit_array, size_t index)
{
	return bit_array ^  (1 << index);
}

bit_arr_ty BitArrMirror(bit_arr_ty bit_array)
{

	size_t i = 0, result = 0;
	for (i = 0; i < BIT_ARR_SIZE; ++i)
	{
		result = ((result << 1) | (bit_array & 1));
		bit_array = bit_array >> 1;
	}
	
	return result;
}

bit_arr_ty BitArrRotateLeft(bit_arr_ty bit_array, size_t shifts)
{
	size_t shift = shifts % BIT_ARR_SIZE;
	return (bit_array << shift)|(bit_array >> (BIT_ARR_SIZE - shift));
}

bit_arr_ty BitArrRotateRight(bit_arr_ty bit_array, size_t shifts)
{
	size_t shift = shifts % BIT_ARR_SIZE;
	return (bit_array >> shift)|(bit_array << (BIT_ARR_SIZE - shift));
}

size_t BitArrCountOn(bit_arr_ty bit_array)
{
	size_t count = 0;
	while(bit_array)
	{
		count += bit_array & 1;
		bit_array >>= 1;
	}
	
	return count;
}

size_t BitArrCountOff(bit_arr_ty bit_array)
{
	return BIT_ARR_SIZE - BitArrCountOn(bit_array);
}

char *BitArrToString(bit_arr_ty bit_array, char *dest_buffer)
{
	char *start_ptr = dest_buffer;
	int count = 0;

	memset(dest_buffer, 0, BIT_ARR_SIZE);

	if(bit_array == 0)
	{	
		*dest_buffer++ = '0';
		*dest_buffer = '\0';
	}

	while(bit_array)
	{
		*dest_buffer = (bit_array & 1) + '0';
		dest_buffer++;
		bit_array >>= 1;
		count++;
	}

	*(start_ptr + count + 1) = '\0';

	Reverse(start_ptr, count);

	return start_ptr; /* return start of ptr for further use */
}










