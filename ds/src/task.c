#include <time.h>       /*  time_t, time, size_t       */
#include <stdlib.h>     /*  malloc, free               */
#include <assert.h>     /*  assert                     */

#include "uid.h"        /*  all                        */
#include "utilities.h"  /* oper_func_ty, clean_func_ty */
#include "task.h"


struct task
{
    ilrd_uid_ty     uid;
    oper_func_ty    operation;
    void            *params;
    clean_func_ty   clean_func;
    time_t          time_to_run;
    size_t          interval;
};


/******************************************************************************/
task_ty *TaskCreate(oper_func_ty operation, size_t interval, 
                    clean_func_ty clean_func, void *params)
{
    task_ty *new_task = NULL;
    time_t curr_time  = 0;
    ilrd_uid_ty uid;

    assert(operation);
    assert(clean_func);
    assert(interval > 0);

    new_task = (task_ty *)malloc(sizeof(task_ty));

    if(NULL == new_task)
    {
        return NULL;
    }

    uid = UIDCreate();

    /* check if valid UID */
    if(UIDIsSame(uid, UIDBadID))
    {
        free(new_task);
        new_task = NULL;
        return NULL;
    }

    curr_time = time(NULL);

    if((time_t)-1 != curr_time)
    {
        new_task->uid = uid;
        new_task->operation = operation;
        new_task->interval = interval;
        TaskUpdateTimeToRun(new_task);
        new_task->params = params;
        new_task->clean_func = clean_func;
    }
    else
    {
        free(new_task);
        new_task = NULL;
    }
    
    return new_task;
}

/******************************************************************************/
void TaskDestroy(task_ty *task)
{
    assert(task);

    task->clean_func(TaskGetUID(task), task->params);

    free(task);
    task = NULL;
}

/*******************************************************************************
 * Performs the operation in "task"
 * returns 0 if "operation" should repeat, 1 if it should stop
 * note: undefined behaviour if "task" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
int TaskRun(task_ty *task)
{
    assert(task);

    return task->operation(task->params);
}

/*******************************************************************************
 * Returns the "task"'s "time_to_run"
 * note: undefined behaviour if "task" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
time_t TaskGetTimeToRun(const task_ty *task)
{
    assert(task);

    return task->time_to_run;
}

/*******************************************************************************
 * Returns the "task"'s "uid"
 * note: undefined behaviour if "task" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
ilrd_uid_ty TaskGetUID(const task_ty *task)
{
    assert(task);

    return task->uid;
}

/*******************************************************************************
 * Updates "task"'s "time_to_run", according to its "interval"
 * note: undefined behaviour if "task" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
void TaskUpdateTimeToRun(task_ty *task)
{
    time_t curr_time = 0;

    assert(task);

    curr_time = time(NULL);
    if((time_t)-1 != curr_time)
    {
        task->time_to_run = curr_time + task->interval;
    }  
}

/*******************************************************************************
 * Returns 1 if "task"'s uid matches "uid", 0 otherwise
 * note: undefined behaviour if "task" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
int TaskIsMatchUID(const task_ty *task, ilrd_uid_ty uid)
{
    assert(task);

    return UIDIsSame(TaskGetUID(task), uid);
}

/*******************************************************************************
 * Returns 1 if "task1"'s "time_to_run" is before "task2"'s "time_to_run",
 * 0 otherwise
 * note: undefined behaviour if "task1" or "task2" are NULL
 * Time Complexity: O(1)
*******************************************************************************/
int TaskIsBefore(const task_ty *task1, const task_ty *task2, void *param)
{
    assert(task1);
    assert(task2);

    (void)param;
    
    return TaskGetTimeToRun(task1) < TaskGetTimeToRun(task2);
}

