#include <stddef.h> 	/* size_t      */
#include <assert.h> 	/* assert 	   */
#include <stdlib.h> 	/* malloc, free*/


#include "sorted_list.h"
#include "dlist.h"


struct sort_list
{
	dlist_ty *dlist;	   /* inner dlist struct   */	
	cmp_func_ty sort_func; /* our sorting criteria */
};

/******************** static functions declaration ****************************/
static sort_list_iter_ty SortListGetIter(dlist_iter_ty dlist_iter);
static dlist_iter_ty GetDlistIterFromSort(sort_list_iter_ty sort_iter);
static dlist_iter_ty FindSortListTailDummy(sort_list_iter_ty sort_iter); 
static sort_list_iter_ty FindNextCmpVal(cmp_func_ty cmp_func, 
	sort_list_iter_ty from, sort_list_iter_ty to, void *data);
/******************************************************************************/



/******************************************************************************/

sort_list_ty *SortedListCreate(cmp_func_ty cmp_func)
{
	sort_list_ty *new_list = NULL;



	assert(cmp_func);

	new_list = (sort_list_ty *)malloc(sizeof(sort_list_ty));

	if(NULL == new_list)
	{
		/* failed */
		return NULL;
	}

	new_list->dlist = DlistCreate();

	if(NULL == new_list->dlist)
	{
		free(new_list);
		new_list = NULL;
		return NULL;
	}

	new_list->sort_func = cmp_func;

	return new_list;
}

/******************************************************************************/

void SortedListDestroy(sort_list_ty *sort_list)
{
	assert(sort_list);

	DlistDestroy(sort_list->dlist);

	free(sort_list);
	sort_list = NULL;
}

/******************************************************************************/

size_t SortedListSize(const sort_list_ty *sort_list)
{
	assert(sort_list);

	return DlistSize(sort_list->dlist);
}

/******************************************************************************/

int SortedListIsEmpty(const sort_list_ty *sort_list)
{
	assert(sort_list);

	return DlistIsEmpty(sort_list->dlist);
}

/******************************************************************************/

sort_list_iter_ty SortedListBegin(const sort_list_ty *sort_list)
{
	assert(sort_list);

	return SortListGetIter(DlistIterBegin(sort_list->dlist));
}

/******************************************************************************/

sort_list_iter_ty SortedListEnd(const sort_list_ty *sort_list)
{
	assert(sort_list);

	return SortListGetIter(DlistIterEnd(sort_list->dlist));
}

/******************************************************************************/

sort_list_iter_ty SortedListNext(sort_list_iter_ty iter)
{	
	return SortListGetIter(DlistIterNext(iter.dlist_iter));
}

/******************************************************************************/

sort_list_iter_ty SortedListPrev(sort_list_iter_ty iter)
{
	return SortListGetIter(DlistIterPrev(iter.dlist_iter));
}

/******************************************************************************/

int SortedListIterIsEqual(sort_list_iter_ty iter1, sort_list_iter_ty iter2)
{
	/* get nodes first for comparing */
	return DlistIterIsEqual(iter1.dlist_iter, iter2.dlist_iter);
}

/******************************************************************************/

void *SortedListGetData(sort_list_iter_ty iter)
{
	return (void *)(DlistIterGetData(iter.dlist_iter));
}

/******************************************************************************/

sort_list_iter_ty SortedListRemove(sort_list_iter_ty iter_to_remove)
{
	
	iter_to_remove.dlist_iter = DlistRemove(GetDlistIterFromSort(iter_to_remove));

	return iter_to_remove;
}

/******************************************************************************/

void *SortedListPopFront(sort_list_ty *sort_list)
{
	assert(sort_list);

	return DlistPopFront(sort_list->dlist);
}

/******************************************************************************/

void *SortedListPopBack(sort_list_ty *sort_list)
{
	assert(sort_list);

	return DlistPopBack(sort_list->dlist);
}

/******************************************************************************/

int SortedListForeach(sort_list_iter_ty from, sort_list_iter_ty to, 
                                            action_func_ty action, void *param)
{
	/* if foreach didn't fail it will return 0 */
	return DlistForEach(GetDlistIterFromSort(from), GetDlistIterFromSort(to), action, param);
}

/******************************************************************************/

sort_list_iter_ty SortedListInsert(sort_list_ty *sort_list, const void *data)
{

    sort_list_iter_ty start;
    sort_list_iter_ty end;
    sort_list_iter_ty found_position;

    assert(sort_list);
    assert(data);

    start = SortedListBegin(sort_list);
    end = SortedListEnd(sort_list);

    /* base case - list is empty so just push to front */
    if(SortedListIsEmpty(sort_list))
    {
        start = SortListGetIter(DlistPushFront(sort_list->dlist, (void *)data));
        return start;
    }

    /* find position where cmp func complies */
    found_position = FindNextCmpVal(sort_list->sort_func, start, 
                                                end, (void *)data);

    /* insert into that position */
    found_position = SortListGetIter(DlistInsert(GetDlistIterFromSort(found_position), (void *)data));

    return found_position;
}

/*********************************Merge****************************************/

void SortedListMerge(sort_list_ty *dest, sort_list_ty *src)
{

	sort_list_iter_ty from_dest = SortedListBegin(dest);
	sort_list_iter_ty to_dest   = SortedListEnd(dest);
	
	sort_list_iter_ty from_src = SortedListBegin(src);
	sort_list_iter_ty to_src   = SortedListEnd(src);

	sort_list_iter_ty where;
	sort_list_iter_ty to;

	void *data = NULL;

	/* if dest is empty simply slice all of src into dest end */
	if(SortedListIsEmpty(dest))
	{
		DlistSplice(GetDlistIterFromSort(SortedListEnd(dest)), 
			GetDlistIterFromSort(SortedListBegin(src)), 
			GetDlistIterFromSort(SortedListEnd(src)));
	}


	/* [from - to) , where */
	while(!SortedListIsEmpty(src))
	{
		from_dest = SortedListBegin(dest);
		from_src = SortedListBegin(src);
		data = SortedListGetData(from_src);
		/* find first value where first element from dest matches our sort func 
		*  -> where can we insert data from src
		* * */
		where = FindNextCmpVal(dest->sort_func, from_dest, to_dest, data);

		/* case where we need to splice 1 element we want to include to */
		if(SortedListIterIsEqual(where, to_dest))
		{
			to = to_src;
		}

		/* find next boundary in src(to) comparing to the element we found in dest 
		* or "how many more can we insert"
		* */
		to = FindNextCmpVal(dest->sort_func, from_src, to_src, SortedListGetData(where));

		/* finally splice these elements into dest */
		DlistSplice(GetDlistIterFromSort(where), GetDlistIterFromSort(from_src)
			, GetDlistIterFromSort(to));
	}

	SortedListDestroy(src);
}

/******************************************************************************/

sort_list_iter_ty SortedListFind(sort_list_ty *list, sort_list_iter_ty from, 
                                 sort_list_iter_ty to, const void *param)
{
	
	while(!SortedListIterIsEqual(from, to))
	{
		if(list->sort_func(SortedListGetData(from), (void *)param) == 0)
		{
			return from;
		}
		from = SortedListNext(from);
	}

	return to;
}

/******************************************************************************/

sort_list_iter_ty SortedListFindIf(sort_list_iter_ty from, sort_list_iter_ty to, 
                                is_match_func_ty match_func, const void *param)
{
	
	dlist_iter_ty dlist_iter = DlistFind(from.dlist_iter, to.dlist_iter, match_func, (void *)param);

	if(FindSortListTailDummy(to) == dlist_iter)
	{
		return to;
	}

	return SortListGetIter(dlist_iter);
}

/******************************************************************************/

dlist_iter_ty FindSortListTailDummy(sort_list_iter_ty sort_iter)
{
	dlist_iter_ty dlist_iter = GetDlistIterFromSort(sort_iter);

	while(NULL != DlistIterNext(dlist_iter))
	{
		dlist_iter = DlistIterNext(dlist_iter);
	}

	return dlist_iter;
} 

/******************************************************************************/

/* find next value for cmp_func evaluation */
sort_list_iter_ty FindNextCmpVal(cmp_func_ty cmp_func, 
	sort_list_iter_ty from, sort_list_iter_ty to, void *data)
{
	while(!SortedListIterIsEqual(from, to))
	{
		/* check if data > from.data */
		if(cmp_func(SortedListGetData(from), data) >= 0)
		{
			return from;
		}
		from = SortedListNext(from);
	}

	return to;
}

sort_list_iter_ty SortListGetIter(dlist_iter_ty dlist_iter)
{
	sort_list_iter_ty sort_iter;

	sort_iter.dlist_iter = dlist_iter;

	return sort_iter;
}

dlist_iter_ty GetDlistIterFromSort(sort_list_iter_ty sort_iter)
{
	dlist_iter_ty dlist_iter = sort_iter.dlist_iter;

	return dlist_iter;
}


