#include <stdio.h>	/* printf */

#define UNUSED(x) (void)x

#include "scheduler.h"
#include "tests.h"
#include "task.h"
#include "uid.h"

/******************************************************************************/
static void TestSchedulerSize();
static void TestSchedulerRun();
static void TestScheduler();
/******************************************************************************/

int OperationFunc1(void *param)
{
	UNUSED(param);
	printf("Operation 1 Happened\n");

	return 0;
}

int OperationFunc2(void *param)
{
	UNUSED(param);
	printf("Operation 2 Happened\n");
	
	return 0;
}

int OperationFunc3(void *param)
{
	UNUSED(param);
	printf("Operation 3 Happened\n");

	return 1;
}

int OperationStop(void *param)
{
	printf("Calling Stop\n");
	SchedulerStop((scheduler_ty *)param);
	return 1;
}

void CleanUp(ilrd_uid_ty uid, void *param)
{
	UNUSED(param);
	UNUSED(uid);

	printf("Clean Happened\n");
}

/******************************** Main ****************************************/

int main()
{
	TestScheduler();

	PASS;

	return 0;
}

/******************************************************************************/

void TestScheduler()
{
	TestSchedulerRun();
	/*TestSchedulerSize();*/
}

void TestSchedulerSize()
{
	scheduler_ty *new_sched = NULL;

	ilrd_uid_ty uid1;
	ilrd_uid_ty uid2;
	ilrd_uid_ty uid3;

	new_sched = SchedulerCreate();

	TEST("SchedulerSize", SchedulerSize(new_sched), 0);
	TEST("SchedulerIsEmpty", SchedulerIsEmpty(new_sched), 1);

	
	/* can use param to set how many times we want to run Op */
	uid1 = SchedulerAddTask(new_sched, 10, OperationFunc1, NULL, CleanUp);
	uid2 = SchedulerAddTask(new_sched, 5, OperationFunc2, NULL, CleanUp);

	uid3 = SchedulerAddTask(new_sched, 25, OperationStop, new_sched, CleanUp);

	TEST("SchedulerSize", SchedulerSize(new_sched), 3);

	SchedulerRemoveTask(new_sched, uid2);

	TEST("SchedulerSize", SchedulerSize(new_sched), 2);

	SchedulerRemoveTask(new_sched, uid1);
	SchedulerRemoveTask(new_sched, uid3);

	TEST("SchedulerIsEmpty", SchedulerIsEmpty(new_sched), 1);

	SchedulerDestroy(new_sched);
}

void TestSchedulerRun()
{
	scheduler_ty *new_sched = NULL;

	ilrd_uid_ty uid1;
	ilrd_uid_ty uid2;
	ilrd_uid_ty uid3;

	/**************************ignore unused warning **************************/
	UNUSED(uid1);
	UNUSED(uid2);
	UNUSED(uid3);
	/**************************************************************************/

	new_sched = SchedulerCreate();

	TEST("SchedulerSize", SchedulerSize(new_sched), 0);
	TEST("SchedulerIsEmpty", SchedulerIsEmpty(new_sched), 1);

	
	uid1 = SchedulerAddTask(new_sched, 3, OperationFunc1, NULL, CleanUp);
	uid2 = SchedulerAddTask(new_sched, 7, OperationFunc2, NULL, CleanUp);

	TEST("SchedulerSize", SchedulerSize(new_sched), 2);

	SchedulerAddTask(new_sched, 10, OperationFunc3, NULL, CleanUp);

	uid3 = SchedulerAddTask(new_sched, 35, OperationStop, new_sched, CleanUp);

	

	SchedulerRun(new_sched);

	SchedulerDestroy(new_sched);
}
