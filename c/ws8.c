/**********************
 * Author: Shaul Rosenberg
 * Reviewer: Nadav
 * */


#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcat sprintf */
#include <assert.h> /* assert */

#include "ws8.h"
/*
*	create an array of struct, each struct instance already knows 
*	what he is, each struct will have a pointer to his own print function,
*	to print his specific type
*	print function pointer will be void* 
*	use union instead of structs 
*	
*	Add(element_t arr, valueToAdd)
*	for(i = 0 ; i< SIZE ; ++i)
*		arr[i].add_element(valueToAdd); //each element will call his own add func
*	 
*	
*
*/
#define BUFFER_SIZE 256
#define UNUSED(x) (void)(x)

/* function signatures  */
static void PrintInt(element_ty *element_array);
static void PrintFloat(element_ty *element_array);
static void PrintStr(element_ty *element_array);
/* Add functions */
static void AddInt(element_ty *element_array, int num_to_add);
static void AddFloat(element_ty *element_array, int num_to_add);
static void AddStr(element_ty *element_array, int num_to_add);
/* clean functions */
static void CleanInt();
static void CleanFloat();
static void CleanStr(element_ty *element_array);



typedef void (*print_func)(); /* params can be anything */
typedef void   (*add_func)();
typedef void (*clean_func)();

struct element
{
    void *key;
    print_func print;
    add_func add;
    clean_func clean;
};


/* Print Functions */
static void PrintStr(element_ty *element_array)
{
   printf("value is : %s\n", (char*)(element_array[2].key));
}

static void PrintFloat(element_ty *element_array)
{
    printf("value is : %f\n",*(float*)(&element_array[1].key));
}

static void PrintInt(element_ty *element_array)
{
    printf("value is : %d\n",*(int*)(&element_array[0].key));
}

void PrintArray(element_ty *element_array)
{
    int i = 0;
    if(element_array == NULL)
    {
        printf("Element Array is NULL. Goodbye!\n");
    }
    assert(element_array != NULL);
    for(i = 0; i < ARR_SIZE; ++i)
    {
        element_array[i].print(element_array);
    }
}


/*************** Add Functions ***************/

static void AddInt(element_ty *element_array, int num_to_add)
{
    *(int *)(&element_array[0].key) += num_to_add;
}

static void AddFloat(element_ty *element_array, int num_to_add)
{
    *(float *)(&element_array[1].key) += num_to_add;
}

static void AddStr(element_ty *element_array, int num_to_add)
{
    char buffer[INT_RANGE];

    int len = sprintf(buffer, "%d", num_to_add) + 1;

    element_array[2].key = (char *)realloc(element_array[2].key , 
    strlen(element_array[2].key) + len);

    strcat(element_array[2].key,buffer);
    
}

void AddToArray(element_ty *element_array, int n)
{
    assert(element_array != NULL);
    int i = 0;
    printf("After Adding %d \n", n);
    for(i = 0; i < ARR_SIZE; ++i)
    {
        element_array[i].add(element_array, n);
    }
}

/********************************************/

static void CleanInt(element_ty *element_array)
{
	UNUSED(element_array);
    /* do nothing */
}

static void CleanFloat(element_ty *element_array)
{
	UNUSED(element_array);
    /* do nothing */
}

static void CleanStr(element_ty *element_array)
{
    printf("freeing %s\n", element_array[2].key);
    free(element_array[2].key);
}

int CleanArray(element_ty *element_array)
{
    int i = 0;
    printf("Clean Function Called\n");
    for(i = 0; i < ARR_SIZE; ++i)
    {
        element_array[i].clean(element_array);
    }
    free(element_array);
    return 0;
}


element_ty *InitArray(void)
{

    element_ty *element_array = NULL;
    
    element_array = (struct element*)malloc(sizeof(struct element) * ARR_SIZE);
    assert(element_array != NULL);

    *(int*)(&element_array[0].key) = 5;
    element_array[0].add   = &AddInt;
    element_array[0].print = &PrintInt;
    element_array[0].clean = &CleanInt;

    *(float*)(&element_array[1].key) = 7.775;
    element_array[1].add   = &AddFloat;
    element_array[1].print = &PrintFloat;
    element_array[1].clean = &CleanFloat;

    element_array[2].key   = (char*)malloc(BUFFER_SIZE);
    assert(element_array[2].key != NULL);
    strcpy(element_array[2].key, "Hello World!");
    element_array[2].add   = &AddStr;
    element_array[2].print = &PrintStr;
    element_array[2].clean = &CleanStr;

    return element_array;
}

















