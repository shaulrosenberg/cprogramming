/*******************************************************************************
 * Author:      Shaul
 * Version:     1.1
*******************************************************************************/
#include <stdio.h>  /* size_t printf */
#include <string.h> /* strcmp        */
#include <math.h>   /* pow           */
    
#include "bit_arr.h"
#include "tests.h"

static void TestBitArrSetAll(void);
static void TestBitArrResetAll(void);
static void TestBitArrSetOn(void);
static void TestBitArrSetOff(void);
static void TestBitArrSetBit(void);
static void TestBitArrGetVal(void);
static void TestBitArrFlip(void);
static void TestBitArrMirror(void);
static void TestBitArrRotateRight(void);
static void TestBitArrRotateLeft(void);
static void TestBitArrCountOn(void);
static void TestBitArrCountOff(void);
static void TestBitArrToString(void);

/******************************************************************************/

int main()
{
    TestBitArrSetAll();
    TestBitArrResetAll();
    TestBitArrSetOn();
    TestBitArrSetOff();
    TestBitArrSetBit();
    TestBitArrGetVal();
    TestBitArrFlip();
    TestBitArrRotateRight();
    TestBitArrRotateLeft();
    TestBitArrMirror();
    TestBitArrCountOn();
    TestBitArrCountOff();
    TestBitArrToString();


    PASS;
    return 0;
}

/******************************************************************************/

void TestBitArrSetAll()
{
    int i = 0;
    size_t test_cases[6] = { 1, 43123, 12, 0, 5555555, 321 };
    for(i = 0; i < 6; ++i)
    {
        TEST("BitArrSetAll", BitArrSetAll(test_cases[i]), ~(test_cases[i] & 0));
    }
}

void TestBitArrResetAll()
{
    int i = 0;
    size_t test_cases[6] = { 1, 43123, 12, 0, 5555555, 321 };
    for(i = 0; i < 6; ++i)
    {
        TEST("BitArrResetAll", BitArrResetAll(test_cases[i]), 0);
    }
}

void TestBitArrSetOn()
{
    int i = 0;
    size_t test_cases[] = {4, 16}; 
    size_t results[] = {12, 24};
    for(i = 0; i < 2; ++i)
    {
        TEST("BitArrSetOn", BitArrSetOn(test_cases[i], 3), results[i]);
    } 
}

void TestBitArrSetOff()
{
    size_t num = 2147614736;
    TEST("BitArrSetOff", BitArrSetOff(num, 4), 2147614720);   
}

void TestBitArrSetBit()
{
    size_t num = 2725;
    TEST("BitArrSetBit", BitArrSetBit(num, 6, 1), 2789);
}
void TestBitArrGetVal()
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {555, 79879, 123134, 0, 1231341};
    size_t results[] = {0, 0, 1, 0, 1};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("BitArrGetVal", BitArrGetVal(nums[i], 7), results[i]);
        ++i;
    }
}

void TestBitArrFlip()
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {555, 79879, 123134, 0, 1231341};
    size_t results[] = {811, 80135, 123390, 256, 1231085};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("BitArrFlip", results[i], BitArrFlip(nums[i], 8));
        ++i;
    }   
}


void TestBitArrMirror(void)
{
    
    TEST("BitArrMirror", BitArrMirror(pow(2,63)+pow(2,62)), 3);

    TEST("BitArrMirror", BitArrMirror(pow(2,63)),1);
}




void TestBitArrRotateRight(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {1, 79879, 123134, 0, 1231341};
    size_t results[] = {16, 1278064, 1970144, 0, 19701456};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrRotateRight", results[i], BitArrRotateRight(nums[i], 60));
        ++i;
    }        
}


void TestBitArrRotateLeft()
{
    size_t i = 0;
    size_t num_of_tests = 5;
    size_t nums[] =    {1, 8, 16, 64, 256};
    size_t results[] = {2, 16, 32, 128, 512};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("BitArrRotateLeft", BitArrRotateLeft(nums[i], 1), results[i]);
        ++i;
    }  
}

void TestBitArrCountOn()
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {56, 23, 456, 4879, 4564564};
    size_t results[] = {3, 4, 4, 7, 10};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("BitArrCountOn", results[i], BitArrCountOn(nums[i]));
        ++i;
    }     
}

void TestBitArrCountOff()
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {56, 23, 456, 4879, 4564564};
    size_t results[] = {61, 60, 60, 57, 54};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("BitArrCountOff", results[i], BitArrCountOff(nums[i]));
        ++i;
    }   
}

void TestBitArrToString()
{
    size_t test_cases[] = {0 , 9, 12, 2456};
    char results[][64] = {
                        {'0', '\0'}, 
                        {'1','0','0','1','\0'}, 
                        {'1','1','0','0','\0'}, 
                        {'1','0','0','1','1','0','0','1','1','0','0','0','\0'}
                        }; 

    /*char results[][64] = { "0", "1001", "1100", "100110011000"};*/

    char buffer[64] = {0};
    size_t i = 0;
    for(i = 0; i < 4; ++i)
    {
        if(strcmp(BitArrToString(test_cases[i], buffer), results[i]) != 0)
        {
            printf("ToString "RED "Failed " DEFAULT "for %s \n" ,buffer);
        }
    }
}






