#include <stdio.h>   /* printf  */
#include <string.h>

#include "../include/slist.h"
#include "tests.h"

#define UNUSED(x) (void)(x)


void TestSlist(void);
void TestForEach(void);
void TestFind(void);

/* test even numbers */
int IsMatch(const void *list_data, void *param)
{
	UNUSED(param);
	if((*(int*)list_data % 2) == 0) return 1;

    return 0;
}

/* ForEach item in list AddOne(item) */
int Add(void *data, void *param)
{
	UNUSED(param);
	*(int*)data += 5;

	return 0;
}



int main()
{
	TestSlist();
	TestFind();
    TestForEach();
	PASS;

	return 0;
}


void TestForEach()
{
	size_t i = 0, size = 0;
	slist_ty *new_list = SlistCreate();
	iter_ty iter_end = NULL;
	iter_ty iter = SlistIterBegin(new_list);

	int elements[5] = {1, 2, 3, 4, 5};
    int elements1[5] = {5, 4, 3, 2, 1};
	action_func_ty action = Add;

	size = sizeof(elements) / sizeof(elements[0]);

    /* added 5 elements to head */
	for(i = 0; i < size; ++i)
	{
		iter = SlistInsert(iter, &elements[i]);
        iter = SlistIterBegin(new_list);
	}

	for(i = 0; i < size; ++i)
	{
		iter = SlistIterNext(iter);
	}

	iter = SlistIterBegin(new_list);
	iter_end = SlistIterEnd(new_list);

	/* for each element in the list add the value of elements[1] - 5 */
	SlistForEach(iter, iter_end, action, &elements[1]);

    iter = SlistIterBegin(new_list);
    /* test against the reversed array + 5 */
    for(i = 0; i < size; ++i)
    {
        TEST("ForEach", *(int*)SlistIterGetData(iter), elements1[i] + 5);
        iter = SlistIterNext(iter);
    }

    SlistDestroy(new_list);
}

void TestFind()
{
    int data_array[5] = {10, 15, 25, 34, 31};
    slist_ty *new_list = SlistCreate();
    iter_ty res = NULL;
    iter_ty start = NULL;
    is_match_func_ty match_func = IsMatch;
    size_t i = 0;
    
    start = SlistIterBegin(new_list);
  
    
    for(i = 0; i < 5; ++i)
    {
        start = SlistInsert(start, &data_array[i]);
        start = SlistIterBegin(new_list);
    }

    res = SlistFind(SlistIterBegin(new_list), SlistIterEnd(new_list), match_func, &data_array[0]);
    TEST("SlistFind", *(int*)SlistIterGetData(res), 34);
    /* returns first even number which is 34 */
    printf("result found for first even number function = %d\n", *(int*)SlistIterGetData(res));

    SlistDestroy(new_list);
}

void TestSlist()
{
	slist_ty *new = NULL;
    int elments[] = {0, 1566, 15, 4, -5};
    iter_ty iters[5];
    iter_ty iter = NULL;
    /*iter_ty other_iter = NULL;*/
    int *res = NULL;
    size_t i = 0;
    size_t num_of_tests = sizeof(elments) / sizeof(elments[0]);
    /*creat new vector */
    new = SlistCreate();
    iter = SlistIterBegin(new);
    while (i < num_of_tests)
    {
        iter = SlistInsert(iter, &elments[i]);
        iter = SlistIterBegin(new);
        iters[i] = SlistIterNext(iter);
        res = (int *)SlistIterGetData(iter);
        TEST("Test SlistInsert/SlistIterGetData", elments[i], *res);
        ++i;
    }
    TEST("Test SlistCount", SlistCount(new), num_of_tests);
    TEST("Test SlistIterIsEqual", SlistIterIsEqual(iters[0],iters[0]), 1);
    TEST("Test SlistIterIsEqual", SlistIterIsEqual(iters[0],iters[4]), 0);
    i = 1;
    while (i < num_of_tests)
    {
        SlistRemove(iters[i]);
        TEST("Test SlistCount", SlistCount(new), num_of_tests - i);
        ++i;
    }

    SlistDestroy(new);
}
