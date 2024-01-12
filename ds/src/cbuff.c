#include <sys/types.h>  /*    ssize_t              */
#include <stddef.h>     /*    offsetof, size_t     */
#include <assert.h>     /*    assert               */
#include <stdlib.h>     /*    malloc,free          */
#include <string.h>     /*    memcpy               */


#include "cbuff.h"

struct c_buff
{
    size_t read_idx;    /* our "front" index to read from        */
    size_t size;        /* number of occupied elements           */
    size_t capacity;    
    char arr[1];
};


c_buff_ty *CBuffCreate(size_t capacity)
{
    /*  pseudo:
    *   allocate (sizeof(struct c_buffer) + sizeof(char) * capacity)
    *   return pointer to start of struct
    * * */
   c_buff_ty *new_buffer = (c_buff_ty*)malloc(offsetof(c_buff_ty, arr) + capacity);

   if(NULL == new_buffer)
   {
        return NULL;
   }

    /* init struct members */
    new_buffer->size = 0;
    new_buffer->read_idx = 0;
    new_buffer->capacity = capacity;

   return new_buffer;
}

void CBuffDestroy(c_buff_ty *buffer)
{
   assert(NULL != buffer);

   free(buffer);
   buffer = NULL;
}

ssize_t CBuffWrite(c_buff_ty *buffer, const void *src, size_t num_bytes)
{
    
    size_t free_space = 0, first_cpy = 0, second_cpy = 0, write_index = 0;
    
    assert(NULL != buffer);
    assert(NULL != src);

    write_index = (buffer->read_idx + buffer->size) % buffer->capacity;
    
    free_space = CBuffFreeSpace(buffer);
    
    if (0 == free_space)
    {
        return -1;
    }
    
    else
    {
        num_bytes = (num_bytes > free_space) ? free_space : num_bytes;
        
        if(buffer->capacity - write_index >= num_bytes)
        {
            memcpy(buffer->arr + write_index , src, num_bytes);
            buffer -> size += num_bytes;
        }
        else
        {
            first_cpy = num_bytes - (buffer->capacity - write_index);
            second_cpy = num_bytes - first_cpy;
            
            memcpy(buffer->arr + write_index , src, first_cpy); 
            src = (char *)src + first_cpy;
            
            memcpy(buffer->arr , src, second_cpy);
            
            buffer->size += num_bytes; 
        }
        
    }
    
    return num_bytes;
}

ssize_t CBuffRead(c_buff_ty *buffer, void *dest, size_t num_bytes)
{
    
    size_t first_cpy = 0, second_cpy = 0;
    
    assert(NULL != buffer);
    assert(NULL != dest);   
    
    if (CBuffIsEmpty(buffer))
    {
        return -1;
    }

    else
    {
        num_bytes = (num_bytes > buffer->size) ? buffer->size : num_bytes;
        
        if((buffer->capacity - buffer->read_idx) >= num_bytes)
        {
            memcpy(dest, buffer->arr + buffer->read_idx , num_bytes);
            buffer->size -= num_bytes;
            buffer->read_idx += num_bytes;
        }
        else
        {
            first_cpy = num_bytes - (buffer->capacity - buffer->read_idx);
            second_cpy = num_bytes - first_cpy;
            /* write from read_idx to end(capacity) */
            memcpy(dest, buffer->arr + buffer->read_idx, first_cpy);
            dest = (char *)dest + first_cpy;
            /* write remaining bytes to start */
            buffer->read_idx = 0;
            memcpy(dest, buffer->arr + buffer->read_idx, second_cpy);
            buffer->size -= num_bytes;
            buffer->read_idx += num_bytes;
        }
        
    }
    
    return num_bytes; 
}




int CBuffIsEmpty(const c_buff_ty *buffer)
{
    assert(NULL != buffer);

    return (buffer->size == 0);
}

size_t CBuffSize(const c_buff_ty *buffer)
{
    assert(NULL != buffer);

    return buffer->size;
}

size_t CBuffFreeSpace(const c_buff_ty *buffer)
{
    assert(NULL != buffer);

    return buffer->capacity - buffer->size;
}


