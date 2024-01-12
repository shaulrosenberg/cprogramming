#ifndef __SLIST2_H__
#define __SLIST2_H__



typedef struct node 
{
	void *data;
	struct node *next;
}node_t;


/******************************************************************************* 
 *  function reverse the list and return the pointer to the first elment
 *  note: undefined behaviour if "head" is NULL 
 *  Time Complexity: O(n)
*******************************************************************************/
node_t *Flip(node_t *head);


/******************************************************************************* 
 *  function check if the slist has loop.
 *  return 1 if true, 0 if not found.
 *  note: undefined behaviour if "head" is NULL 
 *  Time Complexity: O(n)
*******************************************************************************/
int HasLoop(const node_t *head);


/******************************************************************************* 
 *  returns a pointer to the first mutual to both slist if 
 *  note: undefined behaviour if "head" is NULL 
 *  Time Complexity: O(n)
*******************************************************************************/
node_t *FindIntersection(node_t *head1, node_t *head2);
#endif  /*  __SLIST2_H__   */
