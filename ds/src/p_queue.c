#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert		*/
#include <stddef.h>		/* size_t		*/

#include "p_queue.h"
#include "sorted_list.h"

struct p_queue
{
	sort_list_ty *sorted_list;
};

/***************************Function Definitions*******************************/

p_queue_ty *PQueueCreate(cmp_func_ty cmp_priority)
{

	p_queue_ty *new_queue = NULL;

	assert(cmp_priority);

	new_queue = (p_queue_ty *)malloc(sizeof(p_queue_ty));

	if(NULL == new_queue)
	{
		return NULL;
	}

	new_queue->sorted_list = SortedListCreate(cmp_priority);

	if(NULL == new_queue->sorted_list)
	{
		free(new_queue);
		new_queue = NULL;
	}

	return new_queue;
}

/******************************************************************************/

void PQueueDestroy(p_queue_ty *p_queue)
{
	assert(p_queue);

	SortedListDestroy(p_queue->sorted_list);

	free(p_queue);
	p_queue = NULL;
}

/******************************************************************************/

void *PQueuePeek(const p_queue_ty *p_queue)
{
	assert(p_queue);

	return SortedListGetData(SortedListPrev(SortedListEnd(p_queue->sorted_list)));
}

/******************************************************************************/

int PQueueEnqueue(p_queue_ty *p_queue, const void *data)
{
	assert(p_queue);

	return SortedListIterIsEqual(SortedListInsert(p_queue->sorted_list, data), 
		SortedListEnd(p_queue->sorted_list));
}

/******************************************************************************/

void PQueueDequeue(p_queue_ty *p_queue)
{
	assert(p_queue);

	SortedListPopBack(p_queue->sorted_list);
}

/******************************************************************************/

int PQueueIsEmpty(p_queue_ty *p_queue)
{
	assert(p_queue);

	return SortedListIsEmpty(p_queue->sorted_list);
}

/******************************************************************************/

size_t PQueueSize(p_queue_ty *p_queue)
{
	assert(p_queue);

	return SortedListSize(p_queue->sorted_list);
}

/******************************************************************************/

void PQueueClear(p_queue_ty *p_queue)
{

	assert(p_queue);

	while(!PQueueIsEmpty(p_queue))
	{
		PQueueDequeue(p_queue);
	}
}

/******************************************************************************/

void *PQueueErase(p_queue_ty *p_queue, is_match_func_ty match_func, void *param)
{
	sort_list_iter_ty to_erase;

	void *saved_data = NULL;

	assert(p_queue);
	assert(match_func);

	/* search from lowest priority to highest */
	to_erase = SortedListFindIf(SortedListBegin(p_queue->sorted_list), 
		SortedListEnd(p_queue->sorted_list), match_func, param);

	/* Prevent dummy removal if no match is found */
	if(SortedListIterIsEqual(to_erase, SortedListEnd(p_queue->sorted_list)))
	{
		return NULL;
	}

	saved_data = SortedListGetData(to_erase);

	SortedListRemove(to_erase);

	return saved_data;
}



