#include <stdio.h>   /* printf, size_t */
#include <assert.h>  /* assert */
#include <string.h>  /* memmove memcpy memset */
#include <stdlib.h>  /* malloc */
#include "ws9.h"


/* helper function to check alignment 
*  can also return ptr & (ptr-1)
*/
static int IsAligned(void *ptr)
{   
    if((long)ptr % WORD_SIZE == 0) return 1;
    return 0;
}
/* helper function to fill buffer 
*  THIS FUNCTION IS NOT NEEDED
*
*/
static void FillBuffer(void *buffer, int c)
{
    unsigned char *buffer_ptr = buffer;
    size_t count = 0;
    while(buffer_ptr != NULL && count < WORD_SIZE)
    {
        *buffer_ptr = c;
        ++buffer_ptr;
        ++count;
    }
}

/* safer version of memcpy - first copies to buffer and then to str1 - but we were asked to not use extra space */
void *Memmove(void *dest, const void *src, size_t n)
{
    unsigned char *cdest = dest;
    const unsigned char *csrc = src;

    /* src + n < dest - meaning n bytes forward is safe and no overlap (assuming src is defined earlier or comes first in memory)*/
    if(((char*)src) + n < (char*)dest)
    {
        return Memcpy(dest, src, n);
    }

    /* copy backwards */
    cdest += n - 1;
    csrc += n -1;

    while(n > 0)
    {
        *cdest = *csrc;
        --cdest;
        --csrc;
        --n;
    }
    return dest;
}

/* copy bytes to a memory area */
void *Memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *cdest = dest;
    const unsigned char *csrc = src;
    /* no need for buffer */
    while(n > 0)
    {
        if(IsAligned(cdest) && n > WORD_SIZE)
        {
            /* do chunk copy with size_t ptr*/
            *(size_t*)cdest = *(size_t*)csrc;
            cdest += WORD_SIZE;
            csrc += WORD_SIZE;
            n -= WORD_SIZE;
        }
        else
        {
            /* do byte byte */
            *cdest = *csrc;
            ++cdest;
            ++csrc;
            --n;
        }

    }
    
    return dest;
}

/* pseudo - run through dest while we haven't reached size of bytes to replace
*  n > 0, set every byte to c;
* 
*/
void *Memset(void *dest, int c, size_t n)
{
    unsigned char *iterator = dest;
    unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char)*BUFFER_SIZE);
    assert(iterator != NULL);

    FillBuffer(buffer, c);

    while(n > 0)
    {
        if(IsAligned(iterator) && n > WORD_SIZE) /* (size_t*)iterator+1 != NULL */
        {
            /* word chunk set */
            *(size_t*)iterator = *(size_t*)buffer;
            iterator += WORD_SIZE;
            n -= WORD_SIZE;
        }  
        else
        {
            /* byte byte set */
            *iterator++ = c;
            --n; 
        }
    }
   
    free(buffer);
    buffer = NULL;
    return dest;
}







