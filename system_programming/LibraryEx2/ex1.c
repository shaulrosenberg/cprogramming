#include <stdio.h>
#include "ex1.h"

int x = 15;

void PrintGlobalVariableAddress()
{
	printf("%p\n", &x);
}
