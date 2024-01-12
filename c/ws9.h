#ifndef __WS9_H__
#define __WS9_H__
#include <stdio.h> /* size_t */

#define UNUSED(x) (void)(x)
#define BUFFER_SIZE 256
#define WORD_SIZE sizeof(size_t)

/* copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str. */
void *Memset(void *str, int c, size_t n);

/* This function returns a pointer to destination, which is dest. 
*  copies n characters from memory area src to memory area dest.
*/
void *Memcpy(void *dest, const void * src, size_t n);

/* This function returns a pointer to the destination, which is str1. */
void *Memmove(void *dest, const void *src, size_t n);



#endif /* __WS9_H__ */



