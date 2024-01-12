#include <stdio.h>
#include <stdlib.h>

#include "p_queue.h"
#include "tests.h"


static void TestPqueue(void);
static void TestEnqueueDequeue(void);
static void TestClear(void);
static void TestErase(void);

/* data int value is higher prio */
int MyCmpFunc(void *data1, void *data2)
{
	return *(int *)data1 - *(int *)data2;
}

int MyMatchFunc(const void *data, void *param)
{
	(void)param;
	/* match if even number */
	return (*(int *)data % 2) == 0;
}


int main()
{
	TestPqueue();

	PASS;
	return 0;
}

static void TestPqueue()
{
	TestClear();
	TestEnqueueDequeue();
	TestErase();
}

static void TestEnqueueDequeue()
{	
	int data_arr[] = {1,2,3,4,5};

	cmp_func_ty cmp_func = MyCmpFunc;

	p_queue_ty *new_queue = PQueueCreate(cmp_func);

	TEST("PQueueIsEmpty", PQueueIsEmpty(new_queue), 1);

	PQueueEnqueue(new_queue, &data_arr[0]);
	PQueueEnqueue(new_queue, &data_arr[3]);
	PQueueEnqueue(new_queue, &data_arr[4]);

	TEST("PQueueSize", PQueueSize(new_queue), 3);

	TEST("PQueuePeek", *(int *)PQueuePeek(new_queue), 5);

	TEST("PQueueIsEmpty", PQueueIsEmpty(new_queue), 0);

	PQueueDequeue(new_queue);

	TEST("PQueuePeek", *(int *)PQueuePeek(new_queue), 4);

	PQueueDequeue(new_queue);
	PQueueDequeue(new_queue);

	TEST("PQueueIsEmpty", PQueueIsEmpty(new_queue), 1);

	PQueueDestroy(new_queue);
}


static void TestClear(void)
{
	int data_arr[] = {1,2,3,4,5};

	cmp_func_ty cmp_func = MyCmpFunc;

	p_queue_ty *new_queue = PQueueCreate(cmp_func);

	PQueueEnqueue(new_queue, &data_arr[1]);
	PQueueEnqueue(new_queue, &data_arr[4]);
	PQueueEnqueue(new_queue, &data_arr[2]);
	PQueueEnqueue(new_queue, &data_arr[0]);
	PQueueEnqueue(new_queue, &data_arr[3]);

	PQueueDequeue(new_queue);

	TEST("PQueuePeek", *(int *)PQueuePeek(new_queue), 4);

	PQueueClear(new_queue);

	TEST("PQueueClear", PQueueIsEmpty(new_queue), 1);

	PQueueDestroy(new_queue);
}

static void TestErase()
{
	int data_arr[] = {1,2,3,4,5};

	cmp_func_ty cmp_func = MyCmpFunc;

	is_match_func_ty match_func = MyMatchFunc; 

	p_queue_ty *new_queue = PQueueCreate(cmp_func);

	PQueueEnqueue(new_queue, &data_arr[1]);
	PQueueEnqueue(new_queue, &data_arr[4]);
	PQueueEnqueue(new_queue, &data_arr[2]);
	PQueueEnqueue(new_queue, &data_arr[0]);
	PQueueEnqueue(new_queue, &data_arr[3]);

	/* erase lowest prio even number = 2 */
	TEST("PQueueErase", *(int *)PQueueErase(new_queue, match_func, &data_arr[0]), 2);

	/* erase 2nd lowest prio even number = 4 */
	TEST("PQueueErase", *(int *)PQueueErase(new_queue, match_func, &data_arr[0]), 4);

	TEST("PQueueSize", PQueueSize(new_queue), 3);

	PQueueDestroy(new_queue);
}





