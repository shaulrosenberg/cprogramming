#include <stdio.h>  		/* size_t, printf */

#include "../include/queue.h"
#include "../include/tests.h"


void TestEnqueueDequeue(void);
void TestQueuesAppend(void);

int main(void)
{
    TestEnqueueDequeue();
    TestQueuesAppend();
    PASS;

    return 0;
}


void TestEnqueueDequeue()
{
    queue_ty *new_queue = NULL;
    size_t i = 0, size = 0;
    int data_arr[5] = {1, 2, 3, 4, 5};
    size = sizeof(data_arr) / sizeof(data_arr[0]);

    new_queue = QueueCreate();

    for(i = 0; i < size; ++i)
    {
        QueueEnqueue(new_queue, &data_arr[i]);
    }


    TEST("QueueSize and Enqueue", QueueSize(new_queue), size);
    TEST("QueuePeek", *(int*)QueuePeek(new_queue), data_arr[0]);
    TEST("IsEmpty", QueueIsEmpty(new_queue), 0);

    QueueDequeue(new_queue);
    TEST("Dequeue", *(int*)QueuePeek(new_queue), data_arr[1]);

    QueueDestroy(new_queue);
}



void TestQueuesAppend(void)
{
    queue_ty *queue1 = QueueCreate();
    queue_ty *queue2 = QueueCreate();
    
    int data_arr[5] = {1, 2, 3, 4, 5};
    size_t size = sizeof(data_arr) / sizeof(data_arr[0]);


    TEST("IsEmpty", QueueIsEmpty(queue1), 1);
    TEST("IsEmpty", QueueIsEmpty(queue2), 1);
    /* enqueue first 3 elements to queue1 */
    QueueEnqueue(queue1, &data_arr[0]);
    QueueEnqueue(queue1, &data_arr[1]);
    QueueEnqueue(queue1, &data_arr[2]);

    /* enqueue last 2 elements to queue2 */
    QueueEnqueue(queue2, &data_arr[3]);
    QueueEnqueue(queue2, &data_arr[4]);

   
    QueueAppend(queue1, queue2);

    TEST("QueueSize", QueueSize(queue1), size);

    /* dequeue everything - size should be 0 and isEmpty will return 1 */
    while(!QueueIsEmpty(queue1))
    {
        QueueDequeue(queue1);
    }
    
    TEST("QueueSize", QueueSize(queue1), 0);
    
    /* dummy still remains */
    TEST("IsEmpty", QueueIsEmpty(queue1), 1);

    QueueDestroy(queue1);
    
}










