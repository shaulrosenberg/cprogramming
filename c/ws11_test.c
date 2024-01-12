#include <stdlib.h> /* atoi malloc      */
#include <string.h> /* strcpy strcmp    */

#include "tests.h"
#include "ws11.h"

#define HEX 16
#define DECIMAL 10
#define OCTAL 8
#define BINARY 2

/* Test Functions Declaration */
void TestAtoi(void);
void TestAtoiAny(void);
void TestItoa(void);
void TestItoaAny(void);
void TestCheckOneTwo(void);

int main()
{
    TestAtoi();
    TestAtoiAny();
    TestItoa();
    TestItoaAny();
    TestCheckOneTwo();
    TEST("LITTLE_END_MACRO", 1, IS_LITTLE_END);
    PASS;

    return 0;
}


void TestAtoi()
{
    char test_cases[][50] = { "1234", "0", "-99", "56"};
    size_t i = 0;
    int size = sizeof(test_cases)/50;
    for(i = 0; i < size; ++i)
    {
        TEST("Atoi", Atoi(test_cases[i], 10), atoi(test_cases[i]));
    }
    
}

void TestAtoiAny()
{
    size_t i = 0;
    int results[] = {47, 0, 479, 266261};
    int bases[] = {2,8,16,36};
    char *test[15] = {"101111", "0", "1DF", "5PG5"};

    for (i = 0; i < 4; ++i)
    {
        TEST("AnyAtoi", Atoi(test[i], bases[i]), results[i]);            
    }
}

/* just for base 10 */
void TestItoa()
{
    int i = 0;
    int test_cases[4] = { 1 , 55 , -99, 35 };
    char *expected_result[10] = {"1", "55", "-99", "35"};

    char result[64];

    for(i = 0; i < 4; ++i)
    {
        memset(result, 0, 64);
        if(strcmp(expected_result[i], Itoa(test_cases[i], result, 10)) != 0)
        {
            printf(RED "Failed " DEFAULT "for %d\n", test_cases[i]);
        }
    }
}

void TestItoaAny()
{
    int i = 0;

    char *results[] = {"-11101010", "0", "15b3", "-3fg"};

    int test_cases[] = {-234, 0, 5555, -4444};

    int bases[] = {2,8,16,36};

    char buffer[64];

     for(i = 0; i < 4; ++i)
    {
        memset(buffer, 0, 64);
        if(strcmp(results[i], Itoa(test_cases[i], buffer, bases[i])) != 0)
        {
            printf("Itoa " RED "Failed " DEFAULT "for %d\n", test_cases[i]);
        }
    }
}


void TestCheckOneTwo()
{
    /* should return A E F */
    char a[] = "ABCDEFGHA";
    char b[] = "AEFGHIJKLA";
    char c[] = "GHMNOPQR";

    printf("A = %s\nB = %s\nC = %s:\nIn A and B but not in C\n", a, b, c);
    InFirstAndSecondButNotThird(a, b, c);
}









