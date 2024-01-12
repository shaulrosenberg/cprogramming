#include <stdio.h>  /* printf */
#include "ws8.h"




static void TestMacroType();
static void TestMacroMax();
static void TestStructs();

static int TestFunc(int expected, int output, char* FuncName)
{
	if(output != expected)
	{
		printf("%s failed \n", FuncName);
		return 0;
	}
	return 1;
}

void TestStructs()
{
	element_ty *element_array = NULL;

	element_array = InitArray();
    
    PrintArray(element_array);

    AddToArray(element_array, 10);

    PrintArray(element_array);

    CleanArray(element_array);
}


void TestMacroType()
{
    int success_cnt = 0;
	int test_cases = 4;
    int a = 5;
    int b[5] = {1,2,3,4,5};
    int *ptr_int = &a;
    char c = 'a'; 
	
	success_cnt += TestFunc(4, SIZEOF_VAR(a), "SIZEOF_VAR");
	success_cnt += TestFunc(20, SIZEOF_VAR(b), "SIZEOF_VAR");
	success_cnt += TestFunc(1,  SIZEOF_VAR(c), "SIZEOF_VAR");
	success_cnt += TestFunc(8, SIZEOF_VAR(ptr_int), "SIZEOF_VAR");
	
	printf("Sizeofvar Success %d / %d \n", success_cnt, test_cases);
}

void TestMacroMax()
{
	int success_cnt = 0;
	int test_cases = 4;
	int a = 10;
	int b = 7;
	int c = 4;
	
	success_cnt += TestFunc(a, MAX2(a,b), "MAX2");
	success_cnt += TestFunc(a, MAX3(a,c,b), "MAX3");
	success_cnt += TestFunc(b, MAX2(b,c), "MAX2");
	success_cnt += TestFunc(a, MAX2(a,c), "MAX2");
	printf("MAX2 & MAX3 Success %d / %d \n", success_cnt, test_cases);
}


/* for tests */
int main()
{

    TestMacroType();
    
    TestMacroMax();

    TestStructs();


	return 0;
}


