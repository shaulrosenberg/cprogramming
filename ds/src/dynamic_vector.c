#include <stdio.h>  /* size_t printf       */
#include <stdlib.h> /* malloc realloc free */
#include <string.h> /* memmove             */
#include <assert.h> /* assert              */

#include "dynamic_vector.h"

#define GROWTH_FACTOR 2

/* vector struct */
struct d_vector
{
    size_t capacity;
    size_t size;
    size_t element_size;
    void *data_array;
};


d_vector_ty *VectorCreate(size_t capacity, size_t element_size)
{
    d_vector_ty *vector_ptr = NULL;
    vector_ptr = (d_vector_ty*)malloc(sizeof(d_vector_ty));
    
    if(NULL == vector_ptr)
    {
        return NULL;
    }
	
	/* init size, capacity, element_size and data array */
    vector_ptr->capacity = capacity;
    vector_ptr->size = 0;
    vector_ptr->element_size = element_size;
    vector_ptr->data_array = malloc(capacity * element_size);

    /* if data array allocation failed - call destroy */
    if(vector_ptr->data_array == NULL)
    {
        VectorDestroy(vector_ptr);
    }

    return vector_ptr;
}

void VectorDestroy(d_vector_ty *vector_ptr)
{
    free(vector_ptr->data_array);
    vector_ptr->data_array = NULL;
    free(vector_ptr);
    vector_ptr = NULL;
}

int VectorPushBack(d_vector_ty *vector_ptr, const void *element)
{
	/* pseudo : 
    *   if vector is already full - automatically 
    *   multiply its capacity by GROWTH FACTOR (reallocate)
    *   Push item to last position of vector_ptr->data_array
    *   value of last available position pointed to by size
    * */
    char *start = NULL;
    char *end = NULL;
    
    assert(NULL != vector_ptr);
    assert(NULL != element);
    
    /* check capacity and resize if needed */
    if(vector_ptr->size == vector_ptr->capacity)
    {
        vector_ptr = VectorReserve(vector_ptr, vector_ptr->capacity * GROWTH_FACTOR);
    }
    
    /* if realloc failed return 1 */
    if(vector_ptr == NULL)
    {
        return 1; 
    }

    start = vector_ptr->data_array;
    end = start + vector_ptr->size * vector_ptr->element_size;
    memmove(end, element, vector_ptr->element_size);
    ++vector_ptr->size;
    
    return 0;
}

void VectorPopBack(d_vector_ty *vector_ptr)
{   
    assert(NULL != vector_ptr);
    --vector_ptr->size;
}

/* our index starts from 0 to size - 1 */
void *VectorGetAccessToElement(const d_vector_ty *vector_ptr, size_t index)
{
    char *start = NULL;
    char *vector_index = NULL;
    assert(NULL != vector_ptr);
    /* if index > size we consider this an illegal access */
    if(index > vector_ptr->size)
    {
        return NULL;
    }
    start = vector_ptr->data_array;
    /* return starting address of element at index */
    vector_index = start + index * vector_ptr->element_size;
    
    return (void*)vector_index;
}

size_t VectorGetSize(const d_vector_ty *vector_ptr)
{
    /* return vector_ptr->size */
    assert(NULL != vector_ptr);
    return vector_ptr->size;
}

size_t VectorGetCapacity(const d_vector_ty *vector_ptr)
{
    /* return vector_ptr->capacity */
    assert(NULL != vector_ptr);
    return  vector_ptr->capacity;
}

d_vector_ty *VectorReserve(d_vector_ty *vector_ptr, size_t new_capacity)
{
   /* realloc to new capacity if new capacity > old capacity
   *  update capacity to new capacity
   */
   assert(NULL != vector_ptr);
   if(new_capacity > vector_ptr->capacity)
   {
        vector_ptr->data_array = realloc(vector_ptr->data_array, 
        new_capacity * vector_ptr->element_size);
        vector_ptr->capacity = new_capacity;
   }
   
   if(vector_ptr->data_array == NULL)
   {
        VectorDestroy(vector_ptr);
        return NULL;
   }
   
   return vector_ptr;
}

d_vector_ty *VectorShrinkToFit(d_vector_ty *vector_ptr)
{
   assert(NULL != vector_ptr);
   vector_ptr->data_array = realloc(vector_ptr->data_array, 
   vector_ptr->size * vector_ptr->element_size);

   /* if shrink failed we destroy */
   if(vector_ptr->data_array == NULL)
   {
        VectorDestroy(vector_ptr);
        return NULL;
   }
    vector_ptr->capacity = vector_ptr->size;
    
    return vector_ptr;
}


