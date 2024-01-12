#include <stdio.h>		/* size_t printf */
#include <stdlib.h>		/* malloc, free  */

#include "fsa.h"
#include "tests.h"


static void TestFSA();

int main()
{
	TestFSA();

	PASS;

	return 0;
}


void TestFSA()
{
	size_t suggest_size = 0; 
    size_t num_of_blocks = 12;
    size_t block_size = 16;

    void *pointer_malloc = NULL;
    void *alloc = NULL;
    FSA_pool_ty *pool_test; 

    suggest_size = FSASuggestSize(num_of_blocks, block_size);
    
    printf("%ld \n", suggest_size);
    
    pointer_malloc = malloc(suggest_size);
    
    pool_test = FSAInit(pointer_malloc, suggest_size, block_size);

    TEST("FSACountFree", FSACountFree(pool_test), 12);

    alloc = FSAAlloc(pool_test);

    TEST("FSACountFree", FSACountFree(pool_test), 11);
    
    printf("CountFree %ld \n", FSACountFree(pool_test));
    
    free(pointer_malloc);

}