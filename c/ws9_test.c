#include <stdio.h>     /* printf size_t */
#include <string.h>    /* memmove memcpy memset */
#include "ws9.h"

#define TEST_CASES 4

static void TestMemcpy();
static void TestMemmove();
static void TestMemset();


int TestFunc(void* output, void* expected, char *func_name)
{
    unsigned char *out_ptr = output;
    unsigned char *expect_ptr = expected;
    if(out_ptr != expect_ptr)
    {
        printf("%s Failed for output: %s\n", func_name, (char*)output);
        return 0;
    }
    return 1;
}

static void TestMemcpy()
{
    size_t success_count = 0, i = 0;
    char test_cases_src[4][50] = {"HelloMyFriend123", "Hello World123", "SomeText213", "111111111222222222222"};
    char test_cases_dest[4][50];

    for(i = 0; i < 4; ++i)
    {
        success_count += TestFunc(Memcpy(test_cases_dest[i], test_cases_src[i], 10), 
        memcpy(test_cases_dest[i], test_cases_src[i], 10), "Memcpy");
    }
    printf("Memcpy Success %ld / 4 \n", success_count);
}

static void TestMemmove()
{
    size_t success_count = 0, i = 0;
    char test_cases_src[4][50] = {"HelloMyFriend123", "Hello World123", "SomeText213", "111111111222222222222"};
    char test_cases_dest[4][50];

    for(i = 0; i < 4; ++i)
    {
        success_count += TestFunc(Memmove(test_cases_dest[i], test_cases_src[i], 10), 
        memmove(test_cases_dest[i], test_cases_src[i], 10), "Memmove");
    }
    printf("Memmove Success %ld / 4 \n", success_count);
}

static void TestMemset()
{
    size_t success_count = 0, i = 0;
    char test_cases[4][50] = {"HelloMyFriend123", "Hello World", "SomeText213", "111111111222222222222"};

    for(i = 0; i < 4; ++i)
    {
        success_count += TestFunc(Memset(test_cases[i], 'c', 10), 
                        memset(test_cases[i], 'c', 10), "Memset");
    }
    printf("Memset Success %ld / 4 \n", success_count);
}



int main()
{
   
    TestMemmove();
    TestMemcpy();
    TestMemset(); 


    return 0;
}








