#include <assert.h>		/* assert       			*/
#include <stdlib.h>		/* malloc,free  			*/
#include <time.h>		/* time,  time_t, size_t    */
#include <unistd.h>		/* sleep        		    */

#include "utilities.h"	/* cmp_func_ty, 
                            is_match_func_ty,
                            oper_func_ty, 
                            clean_func_ty 
 													*/
#include "p_queue.h"	/* All But PQueueClear	    */

#include "task.h"		/* All Task Functionality   */
#include "scheduler.h"	

#define SUCCESS 0
#define FAILED 1

static int CompareTimeToRun(void *data1, void *data2);
static int CompareUID(const void *ds_data, void *param);

struct scheduler
{
	p_queue_ty *pqueue;
	int stop_flag;		/* 1 = stop running scheduler, 0 - keep running */
};

/******************************************************************************/

scheduler_ty *SchedulerCreate(void)
{
	scheduler_ty *new_sched = NULL;
	p_queue_ty   *p_queue   = NULL;

	new_sched = (scheduler_ty *)malloc(sizeof(scheduler_ty));

	if(NULL == new_sched)
	{
		return NULL;
	}

	p_queue = PQueueCreate(CompareTimeToRun);

	if(NULL == p_queue)
	{
		free(new_sched);
		new_sched = NULL;
	}

	new_sched->pqueue = p_queue;
	new_sched->stop_flag = 0;

	return new_sched;
}

/******************************************************************************/

void SchedulerDestroy(scheduler_ty *scheduler)
{
	assert(scheduler);

	SchedulerClear(scheduler);

	PQueueDestroy(scheduler->pqueue);
	scheduler->pqueue = NULL;

	free(scheduler);
	scheduler = NULL;
}

/******************************************************************************/

ilrd_uid_ty SchedulerAddTask(scheduler_ty *scheduler, size_t interval, 
                            oper_func_ty operation, void *param,
                            clean_func_ty clean_func)
{
	task_ty *new_task = NULL;

	assert(scheduler);
	assert(operation);
	assert(interval > 0);

	new_task = TaskCreate(operation, interval, clean_func, param);

	if(NULL == new_task)
	{
		return UIDBadID;
	}

	/* if Enqueue Failed Destroy Task and return BadUID */
	if(FAILED == PQueueEnqueue(scheduler->pqueue, (void *)new_task))
	{
		TaskDestroy(new_task);
		new_task = NULL;

		return UIDBadID;
	}

	return TaskGetUID(new_task);
}

/******************************************************************************/

int SchedulerRemoveTask(scheduler_ty *scheduler, ilrd_uid_ty uid)
{	
	task_ty *curr_task = NULL;

	assert(scheduler);
	assert(!UIDIsSame(uid, UIDBadID));
	assert(!SchedulerIsEmpty(scheduler));

	/* this will Dequeue and return the data(i.e: "TASK") we want to destroy */
	curr_task = PQueueErase(scheduler->pqueue, CompareUID, &uid);

	if(NULL == curr_task)
	{
		return FAILED;
	}

	TaskDestroy(curr_task);
	curr_task = NULL;

	return SUCCESS;
}

/******************************************************************************/

int SchedulerRun(scheduler_ty *scheduler)
{
	task_ty *curr_task   = NULL;
	time_t time_to_sleep = 0;
	time_t curr_time 	 = 0;

	/* case we restart the queue with remaining jobs */
	scheduler->stop_flag = 0;

	assert(scheduler);

	while(!scheduler->stop_flag && !SchedulerIsEmpty(scheduler))
	{
		curr_task = (task_ty *)PQueuePeek(scheduler->pqueue);

		PQueueDequeue(scheduler->pqueue);

		/* this test could waste time */
		curr_time = time(NULL);

		if((time_t)-1 != curr_time && 
			0 < (time_to_sleep = TaskGetTimeToRun(curr_task) - curr_time))
		{
			sleep(time_to_sleep);
		}
		

		/* if task hasn't finished executing re-position in the queue */
		if(0 == TaskRun(curr_task))
		{
			TaskUpdateTimeToRun(curr_task);
			/* if Enqueue Fails stop running and destroy current task */
			if(FAILED == PQueueEnqueue(scheduler->pqueue, curr_task))
			{
				TaskDestroy(curr_task);
				curr_task = NULL;
				return FAILED;
			}
		}
		else
		{
			TaskDestroy(curr_task);
			curr_task = NULL;
		}
	}

	return SUCCESS;
}

/******************************************************************************/

void SchedulerStop(scheduler_ty *scheduler)
{
	assert(scheduler);

	scheduler->stop_flag = 1;
}

/******************************************************************************/

size_t SchedulerSize(scheduler_ty *scheduler)
{
	assert(scheduler);

	return PQueueSize(scheduler->pqueue);
}

/******************************************************************************/

int SchedulerIsEmpty(scheduler_ty *scheduler)
{
	assert(scheduler);

	return PQueueIsEmpty(scheduler->pqueue);
}

/******************************************************************************/

void SchedulerClear(scheduler_ty *scheduler)
{
	task_ty *curr_task = NULL;

	assert(scheduler);

	/* Free All Inner Task Resources */
	while(!SchedulerIsEmpty(scheduler))
	{
		curr_task = PQueuePeek(scheduler->pqueue);
		TaskDestroy(curr_task);
		curr_task = NULL;
		PQueueDequeue(scheduler->pqueue);
	}
}

/******************************************************************************/


int CompareTimeToRun(void *data1, void *data2)
{
	return TaskGetTimeToRun((task_ty *)data2) - TaskGetTimeToRun((task_ty *)data1);
}

int CompareUID(const void *ds_data, void *param)
{
	return UIDIsSame(TaskGetUID((task_ty *)ds_data), *(ilrd_uid_ty *)param);
}


