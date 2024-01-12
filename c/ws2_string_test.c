#include <stdio.h>		/* size_t printf  			       */
#include <stdlib.h>		/*  malloc free      			   */
#include <strings.h>
#include <string.h>		/* strlen  strncmp 		           */
#include <ctype.h>		/* islower isupper tolower toupper */
#include <assert.h>     /* assert 						   */
#include "ws2_string.h"

/*void TestCmp();
void TestStrLen(); */

void TestStrLen(void);
void TestStrCmp(void);
void TestStrCpy(void);
void TestStrnCpy(void);
void TestStrnCmp(void);
void TestStrCaseCmp(void);
void TestStrChr(void);
void TestStrDup(void);
void TestStrCat(void);
void TestStrnCat(void);
void TestStrStr(void);
void TestStrSpn(void);


int main()
{
	TestStrLen();
	TestStrCmp();
	TestStrCpy();
	TestStrnCpy();
	TestStrnCmp();
	TestStrCaseCmp();
	TestStrChr();
	/*TestStrDup();*/
	/*TestStrCat();*/
	TestStrnCat();
	TestStrStr();
	TestStrSpn();
	return 0;
}


static int TestFunc(int output, int expected, const char *func_name)
{
	if (output != expected)
	{
		printf ("function %s failed \n", func_name);
		return 0;
	}
	return 1;
}

static int TestFuncChar(char *output, char *expected, const char *func_name)
{
	if (output != expected)
	{
		printf ("function %s failed \n", func_name);
		return 0;
	}
	return 1;
} 



void TestStrLen()
{
	
	int i = 0; /* success counter */
	
	char* test_cases[] = {"Hello", "World", "Welcome", "Test"}; 
	int size = sizeof(test_cases)/sizeof(test_cases[0]);
	
	while(i < size)
	{
		if(strlen(test_cases[i]) == StrLen(test_cases[i]))
		{
			printf("Test Case %d Successful\n", i);
			++i;
		}
	}	
}


void TestStrCmp()
{
	size_t i = 0, success_cnt = 0;
	size_t size = 0;
	const char *test_cases[] = {"Hello", "\0", "somerandomtext9993", "^!#$QQ112"};
	const char *test_cases_cmp[] = {"Hello", "HomeLand", "sf35925", "^!#$QQ112"};
	size = sizeof(test_cases) / sizeof(test_cases[0]);
	
	while (i < size)
	{
		success_cnt += TestFunc(StrCmp(test_cases[i], test_cases_cmp[i]), 
		strcmp(test_cases[i], test_cases_cmp[i]), "strcmp");
        ++i;
	}
	
	printf ("test strcmp %lu / %lu Success! \n", success_cnt, size);
}



void TestStrCpy()
{
	const char *test_cases[] = {"Hello", "Safehousqqq", "\0", "SomeText456"};
	char test_dest_cases[20][20];
	size_t size = 0;
	size_t success_cnt = 0;
	size_t i = 0;

	size = sizeof(test_cases) / sizeof(test_cases[0]);
	while (i < size)
	{
		success_cnt += TestFuncChar(StrCpy(test_dest_cases[i], test_cases[i]),
			strcpy(test_dest_cases[i], test_cases[i]), "strcpy");
			++i;
	}
	printf ("In fuction strcpy %lu / %lu Success! \n", success_cnt, size);
}


void TestStrnCpy()
{
	const char *test_cases[] = {"Hello", "\0", "somerandomtext9993", "^!#$QQ112"};
	char test_dest_cases[20][20];
	size_t size = 0;
	size_t success_cnt = 0;
	size_t i = 0;
	size_t n = 5;

	size = sizeof(test_cases) / sizeof(test_cases[0]);
	while (i < size)
	{
		success_cnt += TestFuncChar(StrnCpy(test_dest_cases[i], test_cases[i], n),
			StrnCpy(test_dest_cases[i], test_cases[i], n), "StrnCpy");
			++i;
	}
	printf ("In fuction StrCpy %lu / %lu Success! \n", success_cnt, size);
}

/*  */
void TestStrnCmp()
{
	size_t i = 0, success_cnt = 0;
	size_t size = 0, n = 3;
	const char *test_cases[] = {"Hello", "\0", "somerandomtext9993", "^!#$QQ112"};
	const char *test_cases_cmp[] = {"Hello", "HomeLand", "sf35925", "^!#$QQ112"};
	size = sizeof(test_cases) / sizeof(test_cases[0]);
	
	while (i < size)
	{
		success_cnt += TestFunc(StrnCmp(test_cases[i], test_cases_cmp[i], n), 
		StrnCmp(test_cases[i], test_cases_cmp[i], n), "StrnCmp");
        ++i;
	}
	
	printf ("In fuction StrnCmp %lu / %lu Success! \n", success_cnt, size);
}

void TestStrCaseCmp()
{
	size_t i = 0, success_cnt = 0;
	size_t size = 0;
	const char *test_cases[] = {"Hello", "\0", "somerandomtext9993", "saLsa"};
	const char *test_cases_cmp[] = {"Hello", "homeland", "sf35925", "saLsa"};
	size = sizeof(test_cases) / sizeof(test_cases[0]);
	
	while (i < size)
	{
		success_cnt += TestFunc(StrCaseCmp(test_cases[i], test_cases_cmp[i]), 
		strcasecmp(test_cases[i], test_cases_cmp[i]), "strcasecmp");
        ++i;
	}
	
	printf ("In fuction strcasecmp %lu / %lu Success! \n", success_cnt, size);
}


void TestStrChr()
{
	const char *test_cases[] = {"Hello", "\0", "somerandomtext9993", "aaaa"};
	size_t size = 0, success_cnt = 0;
	size_t i = 0;
	char test_char = 'a';
	size = sizeof(test_cases) / sizeof(test_cases[0]);

	while (i < size)
	{
		if (strchr(test_cases[i], test_char) == StrChr((test_cases[i]), test_char))
		{
			++success_cnt;
			++i;
		}
	}
	printf ("In fuction strchr %lu / %lu Success! \n", success_cnt, size);
}


void TestStrnCat()
{
	const char *test_cases[] = {"Hello", "\0", "somerandomtext9993", "^!#$QQ112"};
	char test_dest_cases[20][20];
	size_t size = 0, success_cnt = 0, i = 0;
	size_t n = 5;

	size = sizeof(test_cases) / sizeof(test_cases[0]);
	while (i < size)
	{
		success_cnt += TestFuncChar(StrnCat(test_dest_cases[i], test_cases[i], n),
			StrnCat(test_dest_cases[i], test_cases[i], n), "StrnCat");
			++i;
	}
	printf ("In fuction Strncat %lu / %lu Success! \n", success_cnt, size);
}


void TestStrStr()
{
	size_t i = 0, success_cnt = 0;
	size_t size = 0;
	const char *test_cases[] = {"rellq", "\0", "456", "#&123#*Th"};
	const char *test_cases_cmp[] = {"Hello", "HomeLand", "789", "963"};
	size = sizeof(test_cases) / sizeof(test_cases[0]);
	
	while (i < size)
	{
		success_cnt += TestFuncChar(StrStr(test_cases[i], test_cases_cmp[i]), 
		strstr(test_cases[i], test_cases_cmp[i]), "strstr");
        ++i;
	}
	
	printf ("In fuction strstr %lu / %lu Success! \n", success_cnt, size);

}

void TestStrSpn()
{
	size_t i = 0, success_cnt = 0;
	size_t size = 0;
	const char *test_cases[] = {"welloq", "\0HomeLand\0", "456", "#&123#*Th"};
	const char *test_cases_cmp[] = {"Hello", "HomeLand", "789", "963"};
	size = sizeof(test_cases) / sizeof(test_cases[0]);
	
	while (i < size)
	{
		success_cnt += TestFunc(StrSpn(test_cases[i], test_cases_cmp[i]), 
		strspn(test_cases[i], test_cases_cmp[i]), "strspn");
        ++i;
	}
	
	printf ("In fuction strspn %lu / %lu Success! \n", success_cnt, size);
}







