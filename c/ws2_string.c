#include <string.h> /* strlen , strcmp, Strncmp, strcpy, Strncpy*/
#include <stdlib.h>	/* malloc */
#include <ctype.h>	/* islower isupper tolower toupper*/
#include <assert.h> /* assert */
#include "ws2_string.h"


size_t StrLen(const char* str)
{
	size_t counter = 0;
	assert(str != NULL);
	while(str[counter] != '\0')
	{
		counter++;
	}
	
	return counter;
}

/* StrCmp 
   	
	while str1 != NULL and str1 == str2

*/
int StrCmp(const char *str1, const char *str2)
{
	assert (str1 != NULL);
	assert(str2 != NULL);
	
	while ((*str1 != '\0') && (*str1 == *str2))
	{
		++str1;
		++str2;
	}
	
	return (*str1 - *str2);
}

/* StrCpy - copy string to src to dst */
char *StrCpy(char *dst, const char *src)
{
	char *ptr = dst;

	assert (NULL != dst);
	assert (NULL != src); 
	while (*src != '\0')
	{
		*dst = *src;
		++dst;
		++src;
	}
	*dst = '\0';
	
	return ptr;
}


/* loop through dst and src while copying character by character and we have not reached n */
char *StrnCpy(char *dst, const char *src, size_t n)
{
	char *tmp = dst;
	size_t i = 0;

	assert (NULL != dst);
	assert (NULL != src);

	for (i = 0; *src != '\0' && i < n; ++i)
	{
		*dst = *src;
		++dst;
		++src;
	}
	while( i < n)
	{
		++i;
		*dst = '\0'; /* if the copied string is shorter than our destination string, the rest will be filled with null terminator */
	}

	return tmp;
}


/* 	compare 2 strings for certain size
	iterate through both strings comparing character by character and also 
	checking that n is not reached. 	*/
int StrnCmp(const char *str1, const char *str2, size_t n)
{
    size_t i = 0;

    assert (NULL != str1);
    assert (NULL != str2);
	while (('\0' != *str1) && (*str1 == *str2) && (i < n))
	{
		++str1;
		++str2;
		++i;
	}
	
	return *str1 - *str2;
}

/* 	iterate through 	*/
int StrCaseCmp(const char *str1, const char *str2)
{
	assert (NULL != str1);
    assert (NULL != str2);

	while (('\0' != *str1) && (tolower(*str1) == (tolower(*str2))))
	{
		++str1;
		++str2;
	}
	
	return *str1 - *str2;
}

/* 	iterate through the string untill we reach char 'c' , stop and return pointer to that location + remaining length(length - location)
	if searched char 'c' is not found return NULL
	while str[i] != '\0' AND str[i] != c
		str++
	return str
	return NULL	*/ 
	
char *StrChr(const char *str, int c)
{
	assert (NULL != str);

	while (('\0' != *str) && (*str != c))
	{
		str++;
	}
	if (*str == c)
	{
		return (char *)str;
	}
	else
	{
		return NULL;
	}
}


/* create a new allocated string and cpy str to it */
char *StrDup(const char *str) 
{
    char *dst = malloc(StrLen(str)+1);

    assert (NULL != str);
	if (dst == NULL)
	{
		return NULL;
	}
	StrCpy(dst, str);
	
	return dst;
}

/* concat 2 strings - destination has to be big enough
	i = strlen(dst)
	for i = strlen(dst) and j = 0
		append src[j] to destination
	add '\0' to the end of our new string
 */
char *StrCat(char *dst, const char *src)
{
	size_t dstLen = StrLen(dst);
	size_t srcLen = StrLen(src);
	size_t i = 0;
	size_t j = 0;

	assert (NULL != dst);
    assert (NULL != src);
	
	for(i = dstLen; j < srcLen ; )
	{
		dst[i] = src[j];
		++i;
		++j;
	}

	dst[dstLen + srcLen] = '\0';
	return dst;
} 

/* 	*/
char *StrnCat(char *dest, const char *src, size_t n)
{
	char *start = dest;
	
	assert (NULL != dest);
    assert (NULL != src);

	while ('\0' != *start)
	{
		++start;
	}
	while ('\0' != *src && n != 0)
	{
		*start = *src;
		start++;
		src++;
		--n;
	}
	*dest = '\0';

	return dest;
}

/*  iterate through the haystack, if we find occurence of the first letter in the substring we strncmp with the size of needle and the rest of the substring */
char *StrStr(const char *haystack, const char *needle)
{
	char *ptr_haystack = 0;
	size_t needleLength = StrLen(needle);
	ptr_haystack = (char*)haystack;
	

	assert (NULL != haystack);
    assert (NULL != needle);
	while ('\0' != *ptr_haystack)
	{
		if ((StrnCmp(ptr_haystack, needle, needleLength)) == 0)
		{
			return ptr_haystack;
		}
		++ptr_haystack;
	}
	
	return NULL;
}

/*   */
size_t StrSpn(const char *s, const char *accept)
{
	size_t len = 0;

	assert (NULL != s);
    assert (NULL != accept);

	while ('\0' != *s && StrChr(accept, *s))
	{
		len++;
		s++;
	}
	
	return len;
}



