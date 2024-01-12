#include <stdio.h> /* printf size_t */
#include <ctype.h> /* toupper */
#include "ws11.h"

#define ASCII_SIZE 256

/* look at first byte(lowest address) from x 
*  if it is 1 we are looking at the LSB first
*	- > Little endian 
*	
*/
int IsLittleEndian(void)
{
	unsigned int x = 1;
	char *c = (char*) &x;

	return (int)*c;
}

/* helper function - convert single char to integer */
static int CharToInt(char ch)
{
    if (ch >= '0' && ch <= '9') 
        {
            return ch - '0';
        }
    ch = toupper(ch);
    if (ch >= 'A' && ch <= 'Z')
    {
        return 10 + (ch - 'A');
    }

    return 0;
}


/* create 3 "LUTS" for the 3 arrays and check if chars from A and B but not in C */
void InFirstAndSecondButNotThird(char A[], char B[], char C[])
{
	char inA[ASCII_SIZE] = {0};
	char inB[ASCII_SIZE] = {0};
	char inC[ASCII_SIZE] = {0};
	int i = 0;

	for(i = 0; A[i] != '\0'; ++i)
	{
		inA[(int)A[i]] = 1;
	}
	for(i = 0; B[i] != '\0'; ++i)
	{
		inB[(int)B[i]] = 1;
	}
	for(i = 0; C[i] != '\0'; ++i)
	{
		inC[(int)C[i]] = 1;
	}
	for(i = 0; i < ASCII_SIZE; ++i)
	{
		if(inA[i] == 1 && inB[i] == 1 && inC[i] == 0)
		{
			printf("%c\n", i);
		}
	}
}

/* helper function for itoa */
static void SwapChars(char *c1, char *c2)
{
	char temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

/* helper function for itoa */
static void ReverseString(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        SwapChars((str+start), (str+end));
        start++;
        end--;
    }
}


char *Itoa(int num, char* str, int base)
{    
	char *start_ptr = str;
	int i = 0;
    int isNegative = 0;
    int remainder = 0;
 
    /* case 0 */
    if (num == 0)
    {
        str[i] = '0';
        ++i;
        str[i] = '\0';
        return str;
    }
    
    /* case negative number */
    if (num < 0 )
    {
        isNegative = 1;
        num = -num;
    }
 
    /* Process individual digits */
    while (num != 0)
    {
        remainder = num % base;
        str[i] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
        ++i;
        num = num/base;
    }
 
    /* If number is negative, append '-' */
    if (isNegative)
    {
         str[i] = '-';
        ++i;
    }
    
    /* append string terminator */
    *(start_ptr + i) = '\0'; 
 
    /* reverse the string */
    ReverseString(start_ptr, i);
 
    return start_ptr;
}

int Atoi(char *str, int base)
{
	int num = 0;
	int isNegative = 1;

	/* case negative num */
	if(*str == '-') 
	{
		isNegative = -1;
		++str;
	}

	while(*str != '\0')
	{
		num = (num * base) + CharToInt(*str);
		++str;
	}

	return num * isNegative;
}











