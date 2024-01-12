#include <stdio.h>	/* size_t printf */
#include <assert.h> /* assert		 */
#include <stdlib.h> /* malloc free   */


#include "../include/slist.h"


typedef struct node
{
	void *data;
	struct node *next;
} node_ty;

struct slist
{
	node_ty *tail;
	node_ty *head;
};

/* return iter.node 				*/
static node_ty *GetNode(iter_ty iter);
/* iter.node = node ; return iter   */
static iter_ty GetIter(node_ty *node);

slist_ty *SlistCreate(void)
{
	/*	pseudo: allocate and create create list handler of type slist 
	*	list now only contains a dummy node
	*	head and tail will first point to the dummy node
	*	head = DUMMY
	*	tail = DUMMY;
	* */
	slist_ty *new_list = NULL;

    new_list = (slist_ty*)malloc(sizeof(slist_ty));

    if (new_list == NULL)
    {   
        return NULL;
    }

    new_list->tail = (node_ty*)malloc(sizeof(node_ty));

    /* tail allocation failed we free new_list */
    if(new_list->tail == NULL)
    {
    	free(new_list);
    	new_list = NULL;
    	return NULL;
    }
    /* dummy node points to NULL and data holds our list handler address */
    new_list->tail->next = NULL;
    new_list->tail->data = new_list;
    /* head points to dummy at first */
    new_list->head = new_list->tail;

    return new_list;
}

/*  */
void SlistDestroy(slist_ty *slist)
{
	/* same as iter */
	node_ty *temp = NULL;
	node_ty *to_delete = NULL;
	temp = SlistIterBegin(slist);
	
	while(temp != NULL)
	{
		to_delete = temp;
		temp = temp->next;
		free(to_delete);
	}

	temp = NULL;
	to_delete = NULL;
	free(slist);
	slist = NULL;		
}

iter_ty SlistInsert(iter_ty where, const void *data)
{
	/* pseudo: we need to change the data of 'where' to
	*  our void *data, save old data of where, and place it 
	*  in our newly created node,
	*	
	*	iter_ty temp = where->next
	*	temp->data = where->data;
	*	
	*	
	*	where->data = data;
	*	where->next = new node
	*	new_node->data = temp->data;
	*	new_node->next = prev;
	*	
	*	
	* */
	node_ty *new_node = NULL;
	slist_ty *tmp = NULL;
    new_node = (node_ty *)malloc(sizeof(node_ty));

	if(NULL == new_node)
	{
		perror("allocation for insert failed. abort\n");
		return NULL;
	}

    assert(NULL != where);
    assert(NULL != data);

    new_node->data = where->data;
    new_node->next = where->next;

    where->data = (void*)data;
    where->next = new_node;

    /* 	when we insert-swapped , if new node->next == NULL
    *	means he is the new tail, we must update it in our slist handler
    *	we update it through the data in our new node now, which holds
    *	a pointer to our slist handler and update the new tail
    *		
    */
    if(NULL == new_node->next)
    {
    	tmp = (slist_ty *)new_node->data;
    	tmp->tail = new_node;
    }

    return where;
}

iter_ty SlistRemove(iter_ty iter_to_remove)
{
	/* remove
	*	pseudo:
	*	
	*	
	*	iter_to_remove->data = iter_to_remove->next->data;
	*	iter_to_remove->next = iter_to_remove->next->next;
	*	free(iter_to_remove->next)
	*	
	* */
	slist_ty *tmp = NULL;
	node_ty *temp = iter_to_remove->next;

	assert(NULL != iter_to_remove);

	/* case we are removing 1 before dummy tail - update new tail */
	if(iter_to_remove->next->next == NULL)
	{
		tmp = (slist_ty*)iter_to_remove->next->data;
		/* new dummy after removing the old one */
		tmp->tail = iter_to_remove;
	}
	
	iter_to_remove->data = iter_to_remove->next->data;
	iter_to_remove->next = iter_to_remove->next->next;

	free(temp);
	temp = NULL;

	return iter_to_remove;
}

size_t SlistCount(const slist_ty *slist)
{
	/* 
	*	while(iter = begin ; iter->next != NULL)
	*		count++
	*	return count;
	**/
	size_t count = 0;
	iter_ty iter = slist->head;
	assert(NULL != slist);
	
	while(NULL != iter->next)
	{
		++count;
		iter = iter->next;
	}

	return count;
}

iter_ty SlistFind(iter_ty from, iter_ty to, is_match_func_ty match_func, void *param)
{
	/* pseudo: while(SlistIterNext() != NULL )
	*	if(is_match_func() == 1) return iter;
	*
	**/
	while(from != to) 
	{
		/* match func will return 1 if it finds a match */
		if (match_func(from->data, param))
		{
			return from;
		}
		from = SlistIterNext(from);
	}
	/* ends up pointing to DUMMY if element wasn't found */
	return to;
}

int SlistForEach(iter_ty from, iter_ty to, action_func_ty action, void *param)
{
	/*	while from != to
	*	do
	*	action(list_data, param);
	*
	* 
	*/
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action);
	
	while(from != to)
	{
		/* action should return 0 for success and 1 if something went wrong */
		if(action(from->data, param))
		{
			return 1;
		}
		from = SlistIterNext(from);
	}
	return 0;
}

iter_ty SlistIterBegin(slist_ty *slist)
{
	assert(NULL != slist);
	return slist->head;
}

iter_ty SlistIterEnd(slist_ty *slist)
{
	assert(NULL != slist);
	return slist->tail;
}

iter_ty SlistIterNext(iter_ty iter)
{
	assert(NULL != iter);
	return iter->next;
}

/* user will need to know what type of elements he is referencing */
void *SlistIterGetData(iter_ty iter)
{
	assert(NULL != iter);
	return iter->data;
}

void SlistIterSetData(iter_ty iter, const void *new_data)
{
	assert(NULL != new_data);
	assert(NULL != iter);
	iter->data = (void*)new_data;
}

int SlistIterIsEqual(iter_ty iterator1, iter_ty iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	return (iterator1 == iterator2);
}

void SlistAppend(slist_ty *dest_slist, slist_ty *src_slist)
{
	/* save old dummy and get new dummy */
 	assert(dest_slist);
 	assert(src_slist);

 	src_slist->tail->data = dest_slist;
 	
 	dest_slist -> tail -> next = src_slist -> head;
 	
 	SlistRemove(dest_slist -> tail);
 	
 	dest_slist -> tail = src_slist -> tail;
 	
 	free(src_slist);
 	src_slist = NULL;
}























