#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/slist_exercises.h"

/* helper functions */
static int GetCount(node_t *head);
static void DestroyList(node_t *head);

/* API */
node_t *Flip(node_t *);
int HasLoop(const node_t *);
node_t *FindIntersection(node_t *, node_t *);


/* another way would just be to make a dummy node
and insert nodes from end to start */
node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *current = head;
	node_t *next = NULL;

	assert(NULL != head);

	while(current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	return head;
}


/* count nodes */
static int GetCount(node_t *head)
{
    node_t *current = head;
    int count = 0;
	
	assert(NULL != head);

    while (current != NULL) {
        count++;
        current = current->next;
    }
 
    return count;
}

/* Destroy List 
static void DestroyList(node_t *head)
{
	node_t *temp = NULL;
	while(NULL != head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}
*/

/* fast pointer moves twice as fast, if there is a loop
* it will catch up to the slow ptr ,otherwise
* we have reached NULL and there is no loop
*/
int HasLoop(const node_t* head)
{
    const node_t *slow_p = head;
	const node_t *fast_p = head;

	assert(NULL != head);

    while (slow_p && fast_p && fast_p->next) 
    {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p) 
        {
            return 1;
        }
    }
    return 0;
}

/* find the larger list, d = abs(list1Len - list2Len) */
node_t *FindIntersection(node_t *head1, node_t *head2)
{
	node_t *slist1 = head1;
	node_t *slist2 = head2;
	size_t slist1_len, slist2_len, d, i =0;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	slist1_len = GetCount(head1);
	slist2_len = GetCount(head2);
	
	if (slist1_len > slist2_len)
	{
		d = slist1_len - slist2_len;
		for (i = 1; i < d; ++i)
		{
			slist1 = slist1 -> next;
		}
		
	}
	else
	{
		d = slist2_len - slist1_len;
		for (i = 1; i < d; ++i)
		{
			slist2 = slist2 -> next;
		}
	}
	
	while (NULL != slist1 && slist2 != slist1 && NULL != slist2)
	{
		slist1 = slist1 -> next;
		slist2 = slist2 -> next;	
	}
	
	if (NULL == slist1 || NULL == slist2)
	{
		return NULL;
	}

	return slist1;
}










