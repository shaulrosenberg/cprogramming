#include <stdio.h>

#include "sorted_list.h"
#include "tests.h"

/* simple cmp func to sort integers in ascending order */
static int MyCmp(void *data1, void *data2)
{
	return *(int *)data2 - *(int *)data1; 
}

void TestSortedList(void);
void TestSortedMerge(void);

int main()
{
	TestSortedList();
	TestSortedMerge();

	PASS;

	return 0;
}


void TestSortedMerge()
{
	int data_arr1[5] = { 32, 55, 3, 4, 5 };
	int data_arr2[5] = { 6, 7, 88, 8, 9 };

	size_t count = 0;
	size_t test_cases = sizeof(data_arr1) / sizeof(data_arr1[0]);

	cmp_func_ty criteria = MyCmp;

	sort_list_ty *dest_list = SortedListCreate(criteria);
	sort_list_ty *src_list = SortedListCreate(criteria);

	/* insert to both lists */
	while(count < test_cases)
	{
		SortedListInsert(dest_list, &data_arr1[count]);
		SortedListInsert(src_list, &data_arr2[count]);
		++count;
	}

	
	SortedListMerge(dest_list, src_list);
	

	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));
	printf("%d\n", *(int *)SortedListPopFront(dest_list));

	/* dest size should be 0 */
	TEST("SortedListSize & Merge", SortedListSize(dest_list), 0);

	TEST("SortedListIsEmpty", SortedListIsEmpty(dest_list), 1);

	/* destroy only dest because src will be destroyed with merge */
	SortedListDestroy(dest_list);
}

void TestSortedList()
{
	int data_arr[5] = { 33,123,45,4,5 };

	cmp_func_ty criteria = MyCmp;

	sort_list_ty *new_list = SortedListCreate(criteria);

	SortedListInsert(new_list, &data_arr[0]);
	SortedListInsert(new_list, &data_arr[1]);
	SortedListInsert(new_list, &data_arr[2]);

	TEST("SortedListSize", SortedListSize(new_list), 3);

	printf("first = %d\n", *(int *)SortedListPopFront(new_list));
	printf("second = %d\n", *(int *)SortedListPopFront(new_list));
	printf("third = %d\n", *(int *)SortedListPopFront(new_list));

	TEST("SortedListIsEmpty", SortedListIsEmpty(new_list), 1);
	
	SortedListDestroy(new_list);
}
