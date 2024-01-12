#include <stddef.h>		/* size_t */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)


typedef struct fsa
{
	void *next_free_block;
} FSA_pool_ty;


/**************************static functions************************************/

static size_t AlignBlockSize(size_t block_size)
{
    return block_size % WORD_SIZE == 0 ? block_size : block_size + (WORD_SIZE - block_size % WORD_SIZE);
}

/******************************************************************************/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	assert(num_of_blocks > 0);

	block_size = AlignBlockSize(block_size);

	return sizeof(FSA_pool_ty) + num_of_blocks * block_size;
}

/******************************************************************************/
FSA_pool_ty *FSAInit(void *mem_pool, size_t FSA_pool_size, size_t block_size)
{
	char *current_block = NULL;
	size_t num_of_blocks = 0;
	size_t i = 0;

	FSA_pool_ty *fsa_handler = NULL;

	assert(mem_pool);

	block_size = AlignBlockSize(block_size);

	/* insert our meta data to start of mempool */
	fsa_handler = (FSA_pool_ty *)mem_pool;

	fsa_handler->next_free_block = (char *)mem_pool + sizeof(FSA_pool_ty);

	num_of_blocks = (FSA_pool_size - sizeof(FSA_pool_ty)) / block_size;

	current_block = fsa_handler->next_free_block;

	for(i = 0; i < num_of_blocks - 1; ++i)
	{
		*(char **)current_block = (char *)current_block + block_size;
		current_block += block_size;
	}

	/* last block data points to NULL */
    *(char **)current_block = NULL;

        return fsa_handler;
}

/******************************************************************************/
void *FSAAlloc(FSA_pool_ty *FSA_pool)
{
	void *block = NULL;

	assert(FSA_pool);

	if(NULL == *(char **)FSA_pool->next_free_block) 
	{
        /* Error: Not enough memory in the pool. */
        return NULL;
    }

    block = FSA_pool->next_free_block;

    FSA_pool->next_free_block = *(char **)block;

    return block;
}

/******************************************************************************/
void FSAFree(FSA_pool_ty *FSA_pool, void *block_to_free)
{
	/* 
	*	FSA_pool_handler->next_free_block = block_to_free;
	*
	* */
	/* get next free block from meta data struct */
	*(char **)block_to_free = FSA_pool->next_free_block;

	FSA_pool->next_free_block = block_to_free;
}

/******************************************************************************/
size_t FSACountFree(FSA_pool_ty *FSA_pool)
{
	size_t count = 0;

	char *current_block = NULL;

	assert(FSA_pool);

	current_block = (char *)FSA_pool->next_free_block;

	while(NULL != current_block)
	{
		current_block = *(char **)current_block;
		++count;
	}

	return count;
}