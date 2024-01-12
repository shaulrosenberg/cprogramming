#include <stdio.h>


/* size_t is defined as unsigned_ Int64 *
* %zd to print				*
* Author: Shaul Rosenberg		* 
* My Reviewer: Nazmeya			*
* TODO: TESTING				*
*****************************************/


void SwapInt(int*, int*);
void TestIntSwap();
void CopyArray(int*, int*, int);
void TestCopyArray();
void SwapSizeT(size_t*, size_t*);
void SwapSizeTPtr(size_t**, size_t**);
void TestSwapPtr(void);




int main()
{
	/* some tests		*/
	TestCopyArray();	
	TestSwapPtr();
	TestIntSwap();
	return 0;
}

void SwapInt(int *num1_ptr, int *num2_ptr)
{
	int tmp = 0;
	tmp = *num1_ptr;
	*num1_ptr = *num2_ptr;
	*num2_ptr = tmp;
}


void CopyArray(int src[], int array_copy[], int size)
{
	int i = 0;
	for( i = 0 ; i < size ; ++i)
	{
		array_copy[i] = src[i];
	}
}



void SwapSizeT(size_t *num1_ptr, size_t *num2_ptr)
{
	size_t tmp = *num1_ptr;
	*num1_ptr = *num2_ptr;
	*num2_ptr = tmp;
}


void SwapSizeTPtr(size_t **ptr1, size_t **ptr2)
{
	SwapSizeT((void*)*ptr1, (void*)*ptr2);
}

void TestIntSwap()
{
	int cases[]  	    = { 500, 300, 123, 5, 1, 0};
	int swapped_cases[] = { 300, 500, 5, 123, 0, 1};
	int size = 6;
	int i = 0;
	int counter = 0;
	
	for(i = 0; i < 6; i += 2)
	{
		SwapInt(&cases[i], &cases[i+1]);
		if(cases[i] == swapped_cases[i])
		{
			counter += 2;
		}
		else
		{
			printf("Test %d Failed\n", i);
		}
	}
	printf("success. %d / %d\n", counter, size);	
}

void TestSwapPtr()
{
	size_t string1 = 50;
	size_t string2 = 25;
	size_t *str1 = &string1;
	size_t *str2 = &string2;
	
	size_t *prev = str1;
	size_t *next = str2;
	
	SwapSizeTPtr((void*)&str1, (void*)&str2);
	if(prev == str2 && next == str1)
	{
		printf("Success \n");
	}
	else
	{
		printf("Failed.\n");
	}
	
}


void TestCopyArray()
{
	int arr1[] = { 1, 2, 3, 4, 5 };
	int arr2[] = { 0, 0, 0, 0, 0 };
	int i = 0;
	int counter = 0;
	int size = 5;
	CopyArray(arr1, arr2, size); /* copy from src arr1 to arr2 */
	for( i = 0; i < size; ++i)
	{
		if(arr2[i] == arr1[i])
		{
			counter++;
		}
		else
		{
			printf("Failed at: %d", i);
		}
	}

	printf("successfully copied %d elements!\n", counter);	
	
}




