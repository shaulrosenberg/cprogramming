#include <stdio.h> /* size_t printf */
#include <stdlib.h>/* malloc */
#include <assert.h>/* assert */
#include "ws3.h"





void TestMatrixRowSum();
void TestJosephus();
void TestPrintEnvVars(char **envp);



int main(int argc, char **argv, char **envp)
{
	
	TestMatrixRowSum();
	TestJosephus();
	PrintTypes();
	/*TestPrintEnvVars(envp);*/
	
	return 0;
}


/*void TestFunc(int expected, int input, char* func)
{
	size_t success_cnt = 0;
	size_t size;
	if(expected == func(input))
	{
		++success_cnt;
		return 1;
	}
	return 0;
}*/


void TestPrintEnvVars(char **envp)
{
	char **tmp = NULL;
	tmp = CopyEnvVars(envp);
	if(tmp == NULL) printf("tmp assign failed");
	PrintEnvVars(envp);	/* tmp is being freed in the print function */
}

static int *NewArr(size_t n)
{
	int *array_ptr = (int*)malloc(sizeof(int)*n);
	assert(NULL != array_ptr);
	return array_ptr;
}

void TestJosephus()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	int size = 5;
	printf("For N = %d Solution = %d(Last Standing)\n", size, Josephus(arr, size));
}

void TestMatrixRowSum()
{
	size_t row = 2;
	size_t col = 5;
	size_t success_cnt = 0;
	size_t i = 0;

	int expected[2] = {15,25};
	int *input = NewArr(row);
	int test_array[10] = {1, 2, 3, 4, 5, 5, 5, 5, 5, 5};
	input = MatrixRowSum(test_array, input, row, col);

	for(i = 0; i < row ; ++i)
	{
		if(input[i] == expected[i])
		{
			++success_cnt;
			printf("Matrix Test  %ld/2 Success \n", success_cnt);
		}
		else
		{
			printf("Failed %ld / 2\n", success_cnt);
		}
		
	}
	
	free(input);
	input = NULL;
}
	
	

