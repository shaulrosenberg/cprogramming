/*******************************************************************************
 * Author:  Shaul
 * Version: 1.6
*******************************************************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>     /*  size_t                      */
#include "uid.h"        /*  ilrd_uid_ty                 */ 
#include "utilities.h"  /* cmp_func_ty clean_func_ty .. */

typedef struct scheduler scheduler_ty;

/*******************************************************************************
 * Create an empty schedule with priorities determined by "cmp_priority", 
 * as defined in "utilities.h"
 * Returns pointer to the schedule on success, NULL otherwise
 * Time Complexity: determined by the used system call complexity
*******************************************************************************/
scheduler_ty *SchedulerCreate(void);

/*******************************************************************************
 * Frees all resources used by "scheduler"
 * note: undefined behaviour if "scheduler" is NULL
 * Time Complexity: determined by the used system call complexity
*******************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler);

/*******************************************************************************
 * Adds an operation to "scheduler" according to it's priority
 * receives the arguments for "operation" and "clean_func" as "params"
 * "operation" and "clean_func" are defined as described in "utilities.h"
 * returns the created task's "uid" if succeeded, "BadUID" otherwise
 * note: undefined behaviour if "scheduler" is NULL, if "interval" equals 0 or 
 * if "operation" or "clean_func" are NULL
 * Time Complexity: ~O(n) (determined by the used system call complexity) 
*******************************************************************************/
ilrd_uid_ty SchedulerAddTask(scheduler_ty *scheduler, size_t interval, 
                            oper_func_ty operation, void *params,
                            clean_func_ty clean_func);

/*******************************************************************************
 * Removes operation specified by "uid"
 * note: undefined behaviour if "scheduler" is empty or NULL 
 *       or if "uid" is "BadUID"
 * Returns: 0 in success, otherwise 1
 * Time Complexity: ~O(n) (determined by the used system call complexity)
*******************************************************************************/
int SchedulerRemoveTask(scheduler_ty *scheduler, ilrd_uid_ty uid);

/*******************************************************************************
 * Starts performing the operations in the scheduler
 * Returns: 0 in success, otherwise 1
 * Time Complexity: O(1)
*******************************************************************************/
int SchedulerRun(scheduler_ty *scheduler);

/*******************************************************************************
 * Stops performing the operations in the scheduler
 * to use it add a task where the operation calls this function
 * Time Complexity: O(1)
*******************************************************************************/
void SchedulerStop(scheduler_ty *scheduler);

/*******************************************************************************
 * Returns the size of the "scheduler"
 * note: undefined behaviour if "scheduler" is NULL
 * Time Complexity: O(n)
*******************************************************************************/
size_t SchedulerSize(scheduler_ty *scheduler);

/*******************************************************************************
 * Returns 1 if the "scheduler" is empty, 0 otherwise
 * note: undefined behaviour if "scheduler" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
int SchedulerIsEmpty(scheduler_ty *scheduler);

/*******************************************************************************
 * Clears all elements from the "scheduler", without deleting "scheduler" itself
 * note: undefined behaviour if "scheduler" is NULL
 * Time Complexity: ~O(n) (determined by the used system call complexity)
*******************************************************************************/
void SchedulerClear(scheduler_ty *scheduler);

#endif /*   __SCHEDULER_H__     */
