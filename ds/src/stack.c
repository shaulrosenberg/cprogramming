#include <stdio.h>      /* size_t        */
#include <assert.h>     /* assert        */
#include <stdlib.h>     /* malloc  free  */
#include <string.h>     /* memmove       */

#include "../include/stack.h"


struct stack
{
    size_t capacity;
    size_t size;
    size_t element_size; /* element size in bytes */
    void *data_array;
};


stack_ty *StackCreate(size_t capacity, size_t size_of_element)
{
    stack_ty *stack_ptr = NULL;
    /* allocate space for the stack struct */
    stack_ptr = (stack_ty*)malloc(sizeof(stack_ty));
    assert(NULL != stack_ptr);
    /* if first allocation succeeded 
    *  we proceed to allocate the data array memory 
    */
    stack_ptr->data_array = malloc(capacity * size_of_element);
    /* if data_array allocation failed we need to destroy the stack */
    if(stack_ptr->data_array == NULL)
    {
        StackDestroy(stack_ptr);
        return NULL;
    }
    stack_ptr->capacity = capacity;
    stack_ptr->element_size = size_of_element;
    /* size or "top" should point to the next available 
    *  place on the stack so we init to 0 
    */
    stack_ptr->size = 0;
    return stack_ptr;
}

/* free internal fields and then the struct itself */
void StackDestroy(stack_ty *stack_ptr)
{
    free(stack_ptr->data_array);
    free(stack_ptr);
    stack_ptr = NULL;
}

/* push element onto top of the stack */
void StackPush(stack_ty *stack_ptr, const void *element)
{
    char *start = NULL;
    char *top = NULL;
    /* top = start + (size * element_size) - 
    *  using char* pointer for single byte jumps as we are talking about 
    *  element size in bytes multiplied by number of elements to reach the top
    */
    start = stack_ptr->data_array;
    top = start + (stack_ptr->size * stack_ptr->element_size); 
    
    /* assert valid stack pointer and element pointer */
    assert(NULL != stack_ptr);
    assert(NULL != element);
   
    /* copy element_size of bytes from src element to dest data_array + size */
    memmove(top, element, stack_ptr->element_size);
    stack_ptr->size++;
}

void StackPop(stack_ty *stack_ptr)
{
    assert(NULL != stack_ptr);
    stack_ptr->size--;
}

/*  return void pointer - the user should know what type 
*   of elements he is pushing and dereference to that type 
*/
void *StackPeek(const stack_ty *stack_ptr)
{
    assert(NULL != stack_ptr);
    /*  looking at (size - 1) because our size or "top" will point to the 
    *   next free location in the stack
    *   which might not be initialized yet and we want the top element
    */
    return ((char*)stack_ptr->data_array + 
    (stack_ptr->element_size * (stack_ptr->size -1)));
}

size_t StackGetSize(const stack_ty *stack_ptr)
{
    return stack_ptr->size;
}

int StackIsEmpty(const stack_ty *stack_ptr)
{
    return stack_ptr->size == 0;
}

size_t StackGetCapacity(const stack_ty *stack_ptr)
{
    return stack_ptr->capacity;
}











