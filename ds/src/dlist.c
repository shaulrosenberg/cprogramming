#include <stdio.h>		/* size_t 	   */
#include <stdlib.h>		/* malloc, free*/
#include <assert.h>		/* assert	   */

#include "dlist.h"



typedef struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
} dlist_node_ty;

struct dlist
{
	struct dlist_node *head;
	struct dlist_node *tail;
};



static dlist_node_ty *DlistGetNode(dlist_iter_ty iter);
static dlist_iter_ty DlistGetIter(dlist_node_ty *node);
static dlist_iter_ty FindTailDummy(dlist_iter_ty iter);
static dlist_iter_ty InsertHelper(dlist_iter_ty where, const void *data);

/* in this case iter is the same as a node pointer so a simple cast is enough
*  but, this may change in the future and we will just need to update	
*  this function for the rest of these functions to work
* */
dlist_node_ty *DlistGetNode(dlist_iter_ty iter)
{
	dlist_node_ty *node = iter; 
	return  node;
}

/* in this case iter is the same as a node pointer so a simple cast is enough
*  but, this may change in the future and we will just need to update	
*  this function for the rest of these functions to work
* */
dlist_iter_ty DlistGetIter(dlist_node_ty *node)
{
	dlist_iter_ty iter = node;
	return iter;
}

/* O(1) "insert" */
dlist_iter_ty InsertHelper(dlist_iter_ty where, const void *data)
{

	dlist_node_ty *new_node = NULL, *where_node = NULL;

	assert(NULL != where);
	assert(NULL != data);

	new_node = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));

	if(NULL == new_node)
	{
		return NULL;
	}

	where_node = DlistGetNode(where);

	new_node->data = (void *)data;
	new_node->prev = where_node->prev;
	new_node->next = where_node;

	where_node->prev->next = new_node;
	where_node->prev = new_node;
	
	where = DlistGetIter(new_node);

	return where;
}


dlist_ty *DlistCreate(void)
{
	
	dlist_ty *new_list = NULL;

	new_list = (dlist_ty *)malloc(sizeof(dlist_ty));

	if(NULL == new_list)
	{
		/* failed allocation */
		return NULL;
	}

	new_list->head = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));

	if(NULL == new_list->head)
	{
		free(new_list);
		new_list = NULL;
		return NULL;
	}

	new_list->tail = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));

	if(NULL == new_list->tail)
	{
		free(new_list->head);
		free(new_list);
		new_list->head = NULL;
		new_list = NULL;
		return NULL;
	}

	new_list->head->prev = NULL;
	new_list->head->next = new_list->tail;
	new_list->head->data = new_list;

	new_list->tail->next = NULL;
	new_list->tail->prev = new_list->head;
	new_list->tail->data = new_list;

	return new_list;
}

void DlistDestroy(dlist_ty *dlist)
{

	dlist_node_ty *current = NULL;
	dlist_node_ty *to_delete = NULL;

	assert(NULL != dlist);

	current = dlist->head;

	while(NULL != current)
	{
		to_delete = current;
		current = current->next;;
		free(to_delete);
	}

	free(dlist);
	to_delete = NULL;
	dlist = NULL;
}

/* this function will not count dummy nodes - as intended */
size_t DlistSize(const dlist_ty *dlist)
{
	
	size_t count = 0;
	dlist_iter_ty iter = NULL;

	assert(NULL != dlist);

	iter = DlistIterBegin(dlist);
	
	while(NULL != DlistIterNext(iter))
	{
		++count;
		iter = DlistIterNext(iter);
	}

	return count;
}

int DlistIsEmpty(const dlist_ty *dlist)
{
	dlist_iter_ty start = NULL, end = NULL;

	assert(NULL != dlist);
	/* get iterators from nodes */
	start = DlistGetIter(dlist->head->next);
	end   = DlistGetIter(dlist->tail);

	return DlistIterIsEqual(start, end);
}

dlist_iter_ty DlistIterBegin(const dlist_ty *dlist)
{
	dlist_iter_ty start = NULL;

	assert(NULL != dlist);

	start = DlistGetIter(dlist->head->next);

	return start;
}

dlist_iter_ty DlistIterEnd(const dlist_ty *dlist)
{
	dlist_iter_ty end = NULL;

	assert(NULL != dlist);

	end = DlistGetIter(dlist->tail);

	return end;
}

dlist_iter_ty DlistIterNext(dlist_iter_ty iter)
{
	assert(NULL != iter);

	return iter->next;
}

dlist_iter_ty DlistIterPrev(dlist_iter_ty iter)
{
	assert(NULL != iter);

	return iter->prev;
}

int DlistIterIsEqual(dlist_iter_ty iter1, dlist_iter_ty iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);

	return (DlistGetNode(iter1) == DlistGetNode(iter2));
}

void *DlistIterGetData(dlist_iter_ty iter)
{
	dlist_node_ty *node = NULL;

	assert(NULL != iter);

	node = DlistGetNode(iter);

	return node->data;
}

dlist_iter_ty DlistPushBack(dlist_ty *dlist, const void *data)
{
	
	dlist_node_ty *new_node = NULL;

	assert(NULL != dlist);
	assert(NULL != data);

	/* O(1) insert */
	new_node = DlistGetNode(InsertHelper(DlistIterEnd(dlist), data));

	if(NULL == new_node)
	{
		return DlistIterEnd(dlist);
	}

	return DlistGetIter(new_node);	
}

void *DlistPopBack(dlist_ty *dlist)
{

	dlist_node_ty *to_be_deleted = NULL;

	void *node_data = NULL;

	assert(NULL != dlist);

	to_be_deleted = dlist->tail->prev;
	/* save data to be returned */
	node_data = (void *)to_be_deleted->data;

	/* change previous node of to_be_deleted to point to dummy */
	to_be_deleted->prev->next = dlist->tail;
	/* dummy prev points to previous of to_be_deleted */
	dlist->tail->prev = to_be_deleted->prev;

	free(to_be_deleted);
	to_be_deleted = NULL;

	return (void *)node_data;
}

dlist_iter_ty DlistPushFront(dlist_ty *dlist, const void *data)
{
	
	dlist_node_ty *new_node = NULL;

	assert(NULL != dlist);
	assert(NULL != data);

	/* O(1) insert */
	new_node = DlistGetNode(InsertHelper(DlistIterBegin(dlist), data));

	if(NULL == new_node)
	{
		return DlistIterEnd(dlist);
	}

	return DlistGetIter(new_node);	
}

void *DlistPopFront(dlist_ty *dlist)
{
	
	dlist_node_ty *to_be_deleted = NULL;

	void *node_data = NULL;

	assert(NULL != dlist);

	/* save node to be deleted */
	to_be_deleted = dlist->head->next;
	/* save data to be returned */
	node_data = (void *)to_be_deleted->data;
	/* update head */
	dlist->head->next = to_be_deleted->next;
	/* update prev of new first valid element in the list */
	to_be_deleted->next->prev = dlist->head;
	/* free to_be_deleted */
	free(to_be_deleted);

	return (void *)node_data;
}

dlist_iter_ty DlistInsert(dlist_iter_ty where, const void *data)
{

	dlist_iter_ty new_node_iter = NULL;

	assert(NULL != where);
	assert(NULL != data);

	new_node_iter = InsertHelper(where, data);
	
	if(NULL == new_node_iter)
	{
		return FindTailDummy(where);
	}

	return new_node_iter;
}

dlist_iter_ty DlistRemove(dlist_iter_ty iter_to_remove)
{

	dlist_node_ty *to_be_removed = NULL;

	assert(NULL != iter_to_remove);

	to_be_removed = DlistGetNode(iter_to_remove);

	/* if user is trying to chain Remove from end or beginning
	*  don't allow removal of dummy nodes
	*  note: API specifies undefined behavior
	* */
	if(NULL == to_be_removed->next || NULL == to_be_removed->prev)
	{	
		return NULL;
	}

	to_be_removed->prev->next = to_be_removed->next;
	to_be_removed->next->prev = to_be_removed->prev;

	/* get next iter */
	iter_to_remove = DlistGetIter(to_be_removed->next);

	free(to_be_removed);
	to_be_removed = NULL;

	/* return next iter */
	return iter_to_remove;
}

dlist_iter_ty DlistFind(dlist_iter_ty from, dlist_iter_ty to, 
                        is_match_func_ty match_func, void *param)
{
	assert(NULL != from);
	assert(NULL != to);

	while(!DlistIterIsEqual(from, to))
	{
		if(match_func(DlistIterGetData(from), param))
		{
			return from;
		}
		from = DlistIterNext(from);
	}

	return to;
}

int DlistMultiFind(dlist_iter_ty from, dlist_iter_ty to, 
                    is_match_func_ty match_func, void *param, 
                    dlist_ty *dest_dlist)
{
	dlist_iter_ty curr = from;

	while(!DlistIterIsEqual(curr, to))
	{
		if(match_func(DlistIterGetData(curr), param) == 1)
		{
			/* could be either push back or push front */
			if(DlistIterEnd(dest_dlist) == DlistPushFront(dest_dlist, DlistIterGetData(curr)))
			/* if push failed return 1 */
			return 1;
		}
		curr = DlistIterNext(curr);
	}

	return 0;
}

int DlistForEach(dlist_iter_ty from, dlist_iter_ty to, action_func_ty action, void *param)
{
	assert(NULL != from);
	assert(NULL != to);

	/* action should return 0 for success */
	while(!DlistIterIsEqual(from, to))
	{
		if(action(DlistIterGetData(from), param))
		{
			return 1;
		}
		from = DlistIterNext(from);
	}

	return 0;
}


dlist_iter_ty DlistSplice(dlist_iter_ty where, dlist_iter_ty from, dlist_iter_ty to)
{
	/* not including to!!!! */
	dlist_node_ty *where_node = NULL, *to_node = NULL, *from_node = NULL;

	dlist_node_ty *saved_where = NULL, *saved_from = NULL;

	assert(NULL != DlistIterPrev(where));
	assert(NULL != DlistIterNext(from));
	assert(NULL != DlistIterPrev(to));

	where_node = DlistGetNode(where);
	from_node  = DlistGetNode(from);
	to_node	   = DlistGetNode(to);

	/* save 'where->prev' and from->prev */
	saved_where = where->prev;
	saved_from = from_node->prev;

	to_node->prev->next = where;

	where->prev = to_node->prev;

	saved_where->next = from_node;
	from_node->prev = saved_where;

	/* update src list */
	to_node->prev = saved_from;
	saved_from->next = to_node;


	where = DlistGetIter(where_node);
	
	return where;
}


/* helper func to find dummy */
dlist_iter_ty FindTailDummy(dlist_iter_ty iter)
{
	assert(NULL != iter);

	while(NULL != DlistIterNext(iter))
	{
		iter = DlistIterNext(iter);
	}

	return iter;
}







