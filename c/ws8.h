#ifndef __WS8_H__
#define __WS8_H__

#define ARR_SIZE 3
#define INT_RANGE 11


/* Ex5 - macro returns max value of 2 numbers*/
#define MAX2(a,b)   (a > b) ? a : b
#define MAX3(a,b,c) MAX2(a, MAX2(b,c))
/* Ex6 - use the type to define a pointer, ++pointer to see where it got us(where we are now - where we were = sizeof) */
#define SIZEOF_VAR(type) (char *)(&type+1)-(char*)(&type)
#define SIZEOF_TYPE(type) (long)((type *)0 + 1)


typedef struct element element_ty;

/* initialize the array of structs */
element_ty *InitArray(void);

/* add an integer to every element in the array */
void AddToArray(element_ty *element_array, int n);

/* print all the array values */
void PrintArray(element_ty *element_array);

/* call this function to free any dynamic allocated memory
*  return 0 for success otherwise non-zero value
*/
int CleanArray(element_ty *element_array);

#endif	/* __WS8_H__ */



