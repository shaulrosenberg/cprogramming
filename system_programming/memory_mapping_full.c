#include <stdio.h>
#include <stdlib.h>

#include "memory_mapping_full.h"

int global_var1 = 1;

const const_global_var1 = 5;

const static const_static_global_var = 10;

static static_global_var1 = 15;

static void StaticFunction()
{

}

void LocalVariables()
{
	int* p_heap_var = (int*)malloc(sizeof(int));
    char* p_heap_var2 = (char*)malloc(sizeof(char)); /* Check allignment */

    char *string_literal = "Aviv";

    int local_var = 1;

    static int static_local_var = 111;

    const static int const_static_local = 20;
    
    const int const_local = 5;
    const int* p_const_local = &const_local;
    const int non_const_local = 5;
    const int* p_non_const_local = &non_const_local;
}

void ExternFunction()
{

}



