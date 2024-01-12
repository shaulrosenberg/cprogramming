#include <stddef.h> /* size_t */

#include "../test/tests.h"
#include "../include/stack.h"

#define TEST_CAPACITY 10

void TestIntStack(void);
void TestCharStack(void);
void TestFloatStack(void);

int main()
{
    TestIntStack();
    TestFloatStack();
    TestCharStack();
    PASS;
    return 0;
}


/*  push a bunch of items = pop them and compare against the items 
*   u pushed in reverse order + size and capacity tests 
*/
void TestIntStack()
{
    size_t i = 0, j = 0;
    int items_to_push[6] = {23, 1, 918, -99, 0, 123};
    size_t items_pushed = sizeof(items_to_push) / sizeof(items_to_push[0]);
    stack_ty *integerStack = StackCreate(TEST_CAPACITY, sizeof(int));

    for(i = 0; i < items_pushed; ++i)
    {
        StackPush(integerStack, &items_to_push[i]);
    }

    TEST("IntegerStack Capacity", StackGetCapacity(integerStack), TEST_CAPACITY);
    TEST("IntegerStack Size", StackGetSize(integerStack), items_pushed);

    for(i = 0, j = StackGetSize(integerStack) - 1; i < StackGetSize(integerStack); ++i, --j)
    {
        
        TEST("TestIntStack", *(int*)StackPeek(integerStack), items_to_push[j]);
        StackPop(integerStack);
    }

    StackDestroy(integerStack);
}

void TestFloatStack()
{
    size_t i = 0, j = 0;
    float items_to_push[6] = {23.23123, 1.0, 918.55, -99.32, 0, 123.00};
    size_t items_pushed = sizeof(items_to_push) / sizeof(items_to_push[0]);
    stack_ty *floatStack = StackCreate(TEST_CAPACITY, sizeof(int));

    for(i = 0; i < items_pushed; ++i)
    {
        StackPush(floatStack, &items_to_push[i]);
    }

    TEST("FloatStack Capacity", StackGetCapacity(floatStack), TEST_CAPACITY);
    TEST("FloatStack Size", StackGetSize(floatStack), items_pushed);

    for(i = 0, j = StackGetSize(floatStack) - 1; i < StackGetSize(floatStack); ++i, --j)
    {
        
        TEST("TestFloatStack", *(float*)StackPeek(floatStack), items_to_push[j]);
        StackPop(floatStack);
    }

    StackDestroy(floatStack);
}

void TestCharStack()
{
    size_t i = 0, j = 0;
    char items_to_push[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    size_t items_pushed = sizeof(items_to_push) / sizeof(items_to_push[0]);
    stack_ty *charStack = StackCreate(TEST_CAPACITY, sizeof(char));

    for(i = 0; i < items_pushed; ++i)
    {
        StackPush(charStack, &items_to_push[i]);
    }

    TEST("CharStack Capacity", StackGetCapacity(charStack), TEST_CAPACITY);
    TEST("CharStack Size", StackGetSize(charStack), items_pushed);

    for(i = 0, j = StackGetSize(charStack) - 1; i < StackGetSize(charStack); ++i, --j)
    {
        TEST("TestCharStack", *(char*)StackPeek(charStack), items_to_push[j]);
        StackPop(charStack);
    }

    StackDestroy(charStack);
}

