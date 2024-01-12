#include <stdio.h>
#include <math.h>
#define BASE 10
#define ARRAY_SIZE 12

/*****************************
* WS1 functions and tests
******************************/


void Hex_To_String()
{
	int hello_array[ARRAY_SIZE] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 			 	 	 	0x6C, 0x64, 0x21};
	int i = 0;
	for(i=0; i<ARRAY_SIZE; i++)
	{	
	printf("%c", hello_array[i]);
	}	
}

double  MyPow(int n)
{

	double result = 1;
	
	if (n == 0)	return 1;
	if (n == 1)	return BASE;
	
	if( n >= 0 )
	{
		while(n != 0)
		{
		result*=BASE;
		n--;
		}
		return result;
		
	}
	else if( n < 0 )
	{
		n = -1 * n;
		while(n != 0)
		{
		result*=BASE;
		n--;
		}
		return 1.0/result;
	}
	return result;
}


int ReverseNum(unsigned int num)
{
	int remainder = 0;
	int result = 0;
	
	if( num == 0 ) return 0;
	while( num != 0 )
	{
		remainder = num%10;
		result = result*10 + remainder;
		num = num / 10;
	}	
	return result;
}

void Swap(int *num1, int *num2)
{
	int temp = *num2;
	
	if(num1 == NULL || num2 == NULL) return;
	*num2 = *num1;
	*num1 = temp;
}

/*****************************
* Let the tests begin!
******************************/

void TestReverseNum()
{
	int num = 0;
	
	printf("Enter a number to reverse: \n");
	if(scanf("%d\n",&num) > 0) printf("Number Entered: %d\n", num);
	printf("Reversed Number = %d", ReverseNum(num));
	
}

void TestMyPow()
{
	int n = 0;
	
	printf("Enter N for POW: ");
	if(scanf("%d", &n) > 0) printf(" Number Entered: %d\n", n);
	if(fabs(pow(10, n) - MyPow(n)) < 0.0001)
	{
		printf("success\n%d", MyPow(n));
	}
	
}

void TestSwap()
{
	int num1 = 8, num2 = 5;
	int *ptr_num1 = &num1; 
	int *ptr_num2 = &num2;
	
	printf("num1 = %d\n num2 = %d\n", num1, num2);
	if(*ptr_num1 == num2 && *ptr_num2 == num1)
	{
		printf(" SUCCESS: num1 = %d\n num2 = %d", num1, num2);
	}
}


int main()
{
	TestMyPow();
	
	return 0;	
}
