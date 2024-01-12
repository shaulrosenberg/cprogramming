#include <stdio.h>  /* printf size_t */
#include <stdlib.h> /* malloc  */
#include <string.h> /* strcpy  */
#include <assert.h> /* assert  */
#include <ctype.h>  /* tolower */
#include "ws3.h"


/* we assume the killer starts from 1 (0 indexing) */
/* find next arr element with value = 1(alive)  */
/* 0 - means dead 1 - alive */

static int FindNextAlive(int arr[], int size, int person)
{
	int i = 0;
	for(i = person % size ; i < size && arr[person] != 0; ++person)
	{
		if(arr[i] == 1) return i;
	}
	return i;
}



int Josephus(int arr[], int size)
{
	int i = 0;
	int kill_count = 0; /* keep track of killed ppl  while(kill_count <  size -1) if kill_count == size-1 this means current index is the last alive */ 
	int person = 0; /* start from killer = first person in the circle */
	/* everyone is alive (1) */
	for( i = 0; i < size ; ++i)
	{
		arr[i] = 1;
	}
	
	/* while kill_count < size - 1 keep killing  (size-1) = only killer alive */
	while(kill_count < size - 1)
	{
		person = FindNextAlive(arr, size, person + 1);
        arr[person] = 0; /* killed */
        printf("killed %d \n", person);
		++kill_count;
		person = FindNextAlive(arr, size, person + 1); /* killer is now the next person alive */
	}
	return person + 1;
}


/* reading an array as matrix and returning result */
int *MatrixRowSum(int *matrix, int *result, int row, int col)
{
	int i = 0;
	int j = 0;
	
	int counter = 0;
	
	for(i = 0; i < col*row; i += col)
	{
		for(j = 0; j < col; ++j)
		{
			result[counter] += matrix[j+i];
		}
		++counter;
	}
	
	return result;
}

/* free the array we allocated */
static void FreeArray(char **ptr)
{
	char **start_ptr = ptr;
	while(NULL != start_ptr)
	{
		free(*start_ptr);
		*start_ptr = NULL;
		++start_ptr;
	}
	free(start_ptr);
	start_ptr = NULL;
}


/* print EnvVars */
void PrintEnvVars(char **envp)
{
	assert(NULL != envp);
	char **env = NULL;
	for(env = envp; *env != NULL; ++env)
	{
		printf("%s\n", *env);
	}
	FreeArray(env);
	env = NULL;
}

/* helper function for CopyEnvVars - to get size of envp(otherwise unknown) */
static int ArrLength(char **arr)
{
	int counter = 0;
	while(*arr != NULL)
	{
		++counter;
		++arr;
	}
	return counter + 1;
}

/* helper function for CopyEnvVars */
static char* ToLowerStr(char *str)
{
	char *str_ptr = str;
	while(*str != '\0')
	{
		*str = tolower(*str);
		++str;
	}
	return str_ptr;
}


/*  */
char **CopyEnvVars(char **envp)
{
	char **new_arr = NULL;
	new_arr = (char**)malloc(ArrLength(envp) * sizeof(char*));
	if(new_arr == NULL) printf("Error Allocating\n");
	char **start_ptr = new_arr;
	assert( NULL != new_arr);
	
	while( *envp != NULL )
	{
			*new_arr = (char*)malloc(strlen(*envp) + 1);
			if(*new_arr == NULL) printf("Error Allocating\n");
			assert( NULL != *new_arr);
			strcpy(*new_arr, ToLowerStr(*envp));
			++new_arr;
			++envp;
	}
	return start_ptr;
}





/********************************/

void PrintTypes()
{
    int dt_int = 0;
    double dt_double = 0;
    long double dt_long_double = 0;
    float dt_float = 0;
    char dt_char = 0;
    size_t dt_size_t = 0;
    unsigned char dt_unsigned_char = 0;
    signed char dt_signed_char = 0;
    short int dt_short_int = 0;
    unsigned int dt_unsigned_int = 0;
    signed int dt_signed_int = 0;
    unsigned short int dt_unsigned_short_int = 0;
    signed short int dt_signed_short_int = 0;
    long int dt_long_int = 0;
    signed long int dt_signed_long = 0;
    unsigned long int dt_unsigned_long_int = 0;
    unsigned long dt_unsigned_long = 0;

    printf("int: %ld \n", sizeof(dt_int));

    printf("double: %ld \n", sizeof(dt_double));

    printf("long double: %ld \n", sizeof(dt_long_double));

    printf("float: %ld \n", sizeof(dt_float));

    printf("char: %ld \n", sizeof(dt_char));

    printf("size_t: %ld \n", sizeof(dt_size_t));

    printf("unsigned char: %ld \n", sizeof(dt_unsigned_char));

    printf("signed char: %ld \n", sizeof(dt_signed_char));

    printf("short int: %ld \n", sizeof(dt_short_int));

    printf("unsigned int: %ld \n", sizeof(dt_unsigned_int));

    printf("long int: %ld \n", sizeof(dt_long_int));

    printf("signed long int: %ld \n", sizeof(dt_signed_long));

    printf("unsigned long int: %ld \n", sizeof(dt_unsigned_long_int));

    printf("unsigned long: %ld \n", sizeof(dt_unsigned_long));

    printf("signed short int %ld \n", sizeof(dt_signed_short_int));

    printf("unsigned short int %ld \n", sizeof(dt_unsigned_short_int));

    printf("signed int %ld \n", sizeof(dt_signed_int));

}


