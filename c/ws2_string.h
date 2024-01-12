#ifndef __WS2_STRING_H__
#define	__WS2_STRING_H__

#include <stddef.h> /* size_t */


/* returns length of a string */
size_t StrLen(const char*);

/* Compare 2 strings - return 0 if equal, negative if str2 > str1, or 1 if it is larger */
int StrCmp(const char*, const char*);

/* copy n size/bytes from src to dst, if src is smaller than dst the rest will be filled with null terminators */
char *StrnCpy(char *dst, const char *src, size_t n);

/* strcpy , copies a string from src to dst including the null terminator '\0' */
char *StrCpy(char *dst, const char *src);

/* strncmp compare 2 strings untill n characters reached or '\0' */
int StrnCmp(const char *str1, const char *str2, size_t num);

/* strcasecmp compare 2 strings without being case sensitive*/
int StrCaseCmp(const char* str1, const char* str2);

/* searches for the first occurrence of the character c (an unsigned char) 
in the string pointed to by the argument str.*/
char *StrChr(const char *str, int c);

/* returns pointer to a null terminated('\0') duplicated string from str1, 
the returned pointer must be passed to free */
char *StrDup( const char *str1 );

/* appends the string pointed to by src to the end of the string pointed to by dest up to n characters long. */
char *StrnCat(char *dst, const char *src, size_t n);

/* strcat */
char *StrCat(char *dst, const char *src);

/* finds the first occurrence of the substring needle 
in the string haystack. The terminating '\0' characters are not compared.*/
char *StrStr(const char *haystack, const char *needle);

/* returns the index of the first char in str1 that doesn't appear in the substring str2*/
size_t StrSpn(const char *str1, const char *str2);

/* Check for palindrome */
int IsPalindrome(const char* str);

#endif
