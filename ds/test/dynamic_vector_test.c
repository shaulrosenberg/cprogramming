#include <stdio.h> /* size_t printf */

#include "dynamic_vector.h"
#include "tests.h"


void TestFloatVector(void);
void TestIntVector(void);


int main()
{
    TestFloatVector();
    TestIntVector();
    PASS;
    return 0;
}



void TestFloatVector(void)
{
    size_t i = 0, size = 0;
    d_vector_ty *floatVector = NULL;
    float to_push[7] = {1.23, 5.55, -45.32, 23.11, 55.32, 100.00, 0.5};
    float extra_elements[3] = {92.2, 85.0, -1.2};

    /* initial vector size is 3, but it will grow by growth factor when we push more than 3 */
    floatVector = VectorCreate(3, sizeof(float));
    TEST("VectorGetCapacity", VectorGetCapacity(floatVector), 3);
    
    size = sizeof(to_push) / sizeof(to_push[0]);
    /* push only 5 elements */
    for(i = 0; i < size - 2; ++i)
    {
        VectorPushBack(floatVector, &to_push[i]);
        TEST("VectorGetAccessToElement", 
        *(float*)VectorGetAccessToElement(floatVector, i), to_push[i]);
    }
	
	printf("TestFloatVector: \n");
    for(i = 0; i < VectorGetSize(floatVector); ++i)
    {
        printf("Element %ld = %f\n", i, 
        *(float*)VectorGetAccessToElement(floatVector, i));
    }
    /* push a 6th element */
    VectorPushBack(floatVector, &to_push[5]);
    /* push a 7th element - vector should grow again */
    VectorPushBack(floatVector, &to_push[6]);
    TEST("VectorGetCapacity", VectorGetCapacity(floatVector), 12);
    /* Shrink test - capacity should be 7 */
    VectorShrinkToFit(floatVector);
    TEST("VectorShrinkToFit", VectorGetCapacity(floatVector), 7);
    /* call reserve set new capacity to 10 */
    floatVector = VectorReserve(floatVector, 10);
    TEST("VectorReserve", VectorGetCapacity(floatVector), 10);
    /* try to push 3 more elements */
    VectorPushBack(floatVector, &extra_elements[0]);
    VectorPushBack(floatVector, &extra_elements[1]);
    VectorPushBack(floatVector, &extra_elements[2]);
    TEST("VectorGetSize", VectorGetSize(floatVector), 10);
    /* 10th element is present */
    printf("Element 10 = %f\n", *(float*)VectorGetAccessToElement(floatVector, 9));

    VectorDestroy(floatVector);
}


void TestIntVector(void)
{
    size_t i = 0, size = 0;
    d_vector_ty *intVector = NULL;
    int to_push[7] = {1, 5, -45, 200, 0, 100, 4444};

    /* initial vector size is 3, but it will grow when we push more than 3 */
    intVector = VectorCreate(3, sizeof(int));
    TEST("VectorGetCapacity", VectorGetCapacity(intVector), 3);
    
    size = sizeof(to_push) / sizeof(to_push[0]);
    /* push only 5 elements */
    for(i = 0; i < size - 2; ++i)
    {
        VectorPushBack(intVector, &to_push[i]);
        TEST("VectorGetAccessToElement", 
        *(int*)VectorGetAccessToElement(intVector, i), to_push[i]);
    }
 
	printf("TestIntVector: \n");
    for(i = 0; i < VectorGetSize(intVector); ++i)
    {
        printf("Element %ld = %d\n", i, 
        *(int*)VectorGetAccessToElement(intVector, i));
    }

    /* push a 6th element */
    VectorPushBack(intVector, &to_push[5]);
    TEST("VectorGetSize", VectorGetSize(intVector), 6);

    /* push a 7th element - vector should grow again */
    VectorPushBack(intVector, &to_push[6]);
    TEST("VectorGetCapacity", VectorGetCapacity(intVector), 12);


    VectorDestroy(intVector);
}
