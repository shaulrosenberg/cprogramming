#include <stdio.h>

#include "../include/slist_exercises.h"
#include "../include/tests.h"

static void TestFlip(void);
static void TestHasLoop(void);
static void TestInterSection(void);


int main(void)
{
	TestFlip();
	TestHasLoop();
	TestInterSection();
	
	PASS;

	return 0;
}

void TestFlip(void)
{
	int test_cases[] = {1, 2, 3, 4, 5};
	node_t head, node1, node2, node3, tail;
	node_t *head_ptr = &head;
	
	head.data = &test_cases[0];
	head.next = &node1;
	
	node1.data = &test_cases[1];
	node1.next = &node2;
	
	node2.data = &test_cases[2];
	node2.next = &node3;
	
	node3.data = &test_cases[3];
	node3.next = &tail;
	
	tail.data = &test_cases[4];
	tail.next = NULL;
	
	Flip(head_ptr);
	
	TEST("testflip-head", head.next, NULL);
	TEST("testflip-node1", node1.next, &head);
	TEST("testflip-node2", node2.next, &node1);
	TEST("testflip-node3", node3.next, &node2);
	TEST("testflip-tail", tail.next, &node3);
	
}

void TestHasLoop(void)
{
	int is_loop = 0;
	int test_cases[] = {1, 2, 3, 4, 5};
	node_t head, node1, node2, node3, tail;
	node_t *ptr = &head;
	
	/*   loop   */
	head.data = &test_cases[0];
	head.next = &node1;
	
	node1.data = &test_cases[1];
	node1.next = &node2;
	
	node2.data = &test_cases[2];
	node2.next = &node3;
	
	node3.data = &test_cases[3];
	node3.next = &node1;
	
	is_loop = HasLoop(ptr);
	
	TEST("TestThereIsLoop", is_loop, 1);
	
	
	/*   no loop   */
	node3.next = &tail;
	tail.data = &test_cases[4];
	tail.next = NULL;
}

void TestInterSection(void)
{
	int test_cases[] = {1, 2, 3, 4, 5, 6 ,7};
	node_t head1, node1_1, node1_2, node1_3, tail1;
	node_t head2, node2_1, node2_2, tail2;
	node_t *ptr1 = &head1;
	node_t *ptr2 = &head2;
	
	
	/*   intersection     */
	head1.data = &test_cases[0];
	head1.next = &node1_1;
	
	head2.data = &test_cases[0];
	head2.next = &node2_1;
	
	node1_1.data = &test_cases[1];
	node1_1.next = &node1_2;
	
	node2_1.data = &test_cases[1];
	node2_1.next = &node1_2;
	
	node1_2.data = &test_cases[2];
	node1_2.next = &node1_3;
	
	node1_3.data = &test_cases[3];
	node1_3.next = &tail1;
	
	tail1.data = &test_cases[4];
	tail1.next = NULL;
	
	ptr1 = FindIntersection(ptr1,ptr2);
	
	TEST("TestInterSection", ptr1, &node1_2);
	
	/*  not intersection   */
	node2_1.data = &test_cases[5];
	node2_1.next = &node2_2;
	
	node2_2.data = &test_cases[6];
	node2_2.next = &tail2;
	
	tail2.data = &test_cases[5];
	tail2.next = NULL;
	
	
	ptr1 = FindIntersection(ptr1,ptr2);
	
	TEST("TestInterSection", ptr1, NULL);
	
	
	
}

