#include <stdio.h>		/* printf, size_t */
#include <assert.h>		/* assert 		  */

#include "dlist.h"
#include "tests.h"



void TestDlist(void);
void TestSplice(void);
void TestMultiFind(void);

int main()
{
	TestMultiFind();
	TestSplice();
	TestDlist();

	PASS;

	return 0;
}

/* simple match to find if data is an even number */
int MatchEvenInt(const void *list_data, void *param)
{
    int num = 0;
    (void)param;
    num = *(int *)list_data;
    return ((num % 2) == 0);
}

int AddOne(void *list_data, void *param)
{
	(void)param;
	if(list_data != NULL)
	{
		*(int *)list_data = (*(int *)list_data) + 1;
		return 0;
	}
	return 1;
}

void TestSplice()
{
	dlist_ty *first_list = DlistCreate();
	dlist_ty *second_list = DlistCreate();

	DlistPushFront(first_list, "Hello1");
	DlistPushFront(first_list, "World1");
	DlistPushFront(first_list, "List1");

	DlistPushFront(second_list, "Hello2");
	DlistPushFront(second_list, "World2");
	DlistPushFront(second_list, "List2");

	/* add all element from second list to first list up to tail
	*	size should now be 6
	* */
	DlistSplice(DlistIterBegin(first_list), 
		DlistIterBegin(second_list), DlistIterEnd(second_list));

	TEST("DlistSize", DlistSize(first_list), 6);

	DlistDestroy(first_list);
	DlistDestroy(second_list);
}

void TestDlist()
{
	dlist_ty *new_list = DlistCreate();

	DlistPushFront(new_list, "Hello");
	DlistPushFront(new_list, "MyLea");
	DlistPushFront(new_list, "World");
	
	TEST("DlistSize", DlistSize(new_list), 3);

	printf("Popped Front: %s\n", (char*)DlistPopFront(new_list));

	TEST("DlistSize", DlistSize(new_list), 2);

	printf("Popped Back: %s\n", (char*)DlistPopBack(new_list));

	TEST("DlistSize", DlistSize(new_list), 1);

	DlistRemove(DlistIterBegin(new_list));

	TEST("DlistIsEmpty", DlistIsEmpty(new_list), 1);

	DlistInsert(DlistIterEnd(new_list), "Last");

	TEST("DlistSize", DlistSize(new_list), 1);

	DlistDestroy(new_list);
}

/* Test MultiFind and ForEach */
void TestMultiFind()
{
	int int_array[7] = {1,2,3,4,5,6,7};

	is_match_func_ty match_func = MatchEvenInt;

	action_func_ty action = AddOne;

	dlist_ty *list_one = DlistCreate();
	dlist_ty *list_two = DlistCreate();

	DlistPushFront(list_one, &int_array[0]);
	DlistPushFront(list_one, &int_array[1]);
	DlistPushFront(list_one, &int_array[2]);
	DlistPushFront(list_one, &int_array[3]);
	/* list_one = 4,3,2,1 size = 4*/

	DlistPushFront(list_two, &int_array[4]);
	DlistPushFront(list_two, &int_array[5]);
	DlistPushFront(list_two, &int_array[6]);
	/* list_two = 7,6,5  size = 3*/

	DlistMultiFind(DlistIterBegin(list_one), DlistIterEnd(list_one), match_func
		,&int_array[0] , list_two);

	/* Add 1 to each element in list_one */
	DlistForEach(DlistIterBegin(list_one), DlistIterEnd(list_one), action, &int_array[0]);


	TEST("DlistForEach", *(int *)DlistPopFront(list_one), 5);
	TEST("DlistForEach", *(int *)DlistPopFront(list_one), 4);
	TEST("DlistForEach", *(int *)DlistPopFront(list_one), 3);
	TEST("DlistForEach", *(int *)DlistPopFront(list_one), 2);
	
	DlistDestroy(list_one);
	DlistDestroy(list_two);
}












