#include <stdio.h>
#include <stdlib.h>

#include "foo.h"

#define STRLEN 20

/* const and non const global variables */
int size_g = 5;
const int const_global_var = 10;
static int static_global_var = 99;
/****************************************/

extern int bar(int x);

static int foo(int x)
{
	return x*2;
}

int HeapGrowth(int n)
{
	int x1 = 5;
	int x2 = 10;

	int *dynamic_int = (int *)malloc(sizeof(int));

	if(n == 0)
		return 1;

	*dynamic_int = n;

	printf("%d\n", *dynamic_int);

	return HeapGrowth(n-1) - 1;
}

int main(int argc, char **argv, char **envp)
{
	int num1 = 2;
	int num3 = 12;

	int i = 0;

	const int num2 = 5;

	char *string_literal = "Hello!";

	char *dynamic_string = (char *)malloc(STRLEN);

	HeapGrowth(num3);

	foo(num3);
	bar(num1);

	free(dynamic_string);

	return 0;
}

