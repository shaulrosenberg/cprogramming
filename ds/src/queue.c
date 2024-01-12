#include <stdio.h>		/* size_t, printf */
#include <stdlib.h> 	/* malloc, free   */
#include <assert.h> 	/* assert 		  */

#include "../include/queue.h"
#include "../include/slist.h"
#include "slist.c"

struct queue
{
	slist_ty *list;
};

queue_ty *QueueCreate(void)
{
	queue_ty *queue = NULL;
	queue = (queue_ty*)malloc(sizeof(queue_ty));

	if(NULL == queue)
	{
		perror("Queue Allocation FAILED. abort.");
		return NULL;
	}

	queue->list = SlistCreate();

	if(NULL == queue->list)
	{
		perror("queue->list Failed.");
		free(queue);
		queue = NULL;
		return NULL;
	}

	return queue;
}


void QueueDestroy(queue_ty *queue)
{
	/*
	*	free inner slist struct
	*	call SlistDestroy();
	*	free(queue);
	* */
	assert(NULL != queue);

	SlistDestroy(queue->list);
	free(queue);
	queue = NULL;
}

void *QueuePeek(const queue_ty *queue)
{
	/*
	*	return front->data
	*	SlistGetIterData(SlistIterBegin(queue->list))
	* */
	assert(NULL != queue);

	return SlistIterGetData(SlistIterBegin(queue->list));
}

int QueueEnqueue(queue_ty *queue, const void *data)
{
	assert(NULL != data);
	assert(NULL != queue);
	/* push item to rear */
	if(NULL == SlistInsert(SlistIterEnd(queue->list), data))
	{
		return 1;
	}

	return 0;
}

void QueueDequeue(queue_ty *queue)
{
	assert(NULL != queue);
	/* remove element in the front */
	SlistRemove(SlistIterBegin(queue->list));
}

int QueueIsEmpty(queue_ty *queue)
{
	/* if (rear == front) -> queue is empty */
	assert(NULL != queue);

	return SlistIterIsEqual(SlistIterBegin(queue->list), SlistIterEnd(queue->list));
}


size_t QueueSize(queue_ty *queue)
{
	assert(NULL != queue);

	return SlistCount(queue->list);
}

void QueueAppend(queue_ty *dest_queue, queue_ty *src_queue)
{
	/* 
	*	pseudo: append the start of queue_list src to end of dest->queue_list;
	*	keep dest dummy node
	*	dest->list->tail->next = src->list->head;
	*	update dummy 
	* */
	assert(NULL != dest_queue);
	assert(NULL != src_queue);
	
	SlistAppend(dest_queue->list, src_queue->list);

	free(src_queue);
	src_queue = NULL;
}







