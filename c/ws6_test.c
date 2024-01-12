#include <stdio.h> /* printf */
#include <math.h>  /*  pow   */
#include "ws6.h" 

#define TEST_CASES 4

static int TestFunc(int output, int expected_output, const char *func_name);
static void TestPow2(void);
static void TestIsPowTwoLoop(void);
static void TestIsPowTwo(void);
static void TestAddOne(void);
static void TestThreeBitSet(void);
static void TestByteMirror(void);
static void TestByteMirrorNoLoop(void);
static void TestSixTwo(void);
static void TestSixOrTwo(void);
static void TestFloatToBinary(void);

int main(void)
{
	TestPow2();
	TestIsPowTwo();
	TestIsPowTwoLoop();
	TestAddOne();
	TestThreeBitSet();
	TestByteMirror();
	TestByteMirrorNoLoop();
	TestSixTwo();
	TestSixOrTwo();
	TestFloatToBinary();
	return 0;
}

static int TestFunc(int output, int expected, const char *func)
{
	if (output != expected)
	{
		printf ("function %s failed \n", func);
		return 0;
	}
	return 1;
}

static void TestPow2(void)
{
	int i = 0;
	int success_cnt = 0;
	int temp_result = 0;
	int x_num[TEST_CASES] = {1, 2, 3, 4};
	int y_num[TEST_CASES] = {5, 6, 7, 8};
	
	while (i < TEST_CASES)
	{
		temp_result = x_num[i] * (pow(2,y_num[i]));
		success_cnt += TestFunc(temp_result, Pow2(x_num[i],y_num[i]), "Pow2");
        ++i;
	}
	
	printf ("In function Pow2 %d / 4 success \n", success_cnt);
}

static void TestIsPowTwoLoop(void)
{
	int i = 0;
	int success_cnt = 0;
	int nums[TEST_CASES] = {3, 1, 128, 12};
	int results[TEST_CASES] = {0, 1, 1, 0};
	
	while (i < TEST_CASES)
	{
		success_cnt += TestFunc(results[i], IsPowTwo(nums[i]), "IsPow");
        ++i;
	}
	
	printf ("In function IsPow %d / 4 success \n", success_cnt);
}

static void TestIsPowTwo(void)
{
	int i = 0;
	int success_cnt = 0;
	int nums[TEST_CASES] = {3, 1, 64, 12};
	int results[TEST_CASES] = {0, 1, 1, 0};
	
	while (i < TEST_CASES)
	{
		success_cnt += TestFunc(results[i], IsPowTwo(nums[i]), "IsPowTwo");
        ++i;
	}
	
	printf ("In function IsPowTwo %d / 4 success \n", success_cnt);
}

static void TestAddOne(void)
{
	int i = 0;
	int success_cnt = 0;
	int nums[TEST_CASES] = {0, 1, 64, 14};
	int results[TEST_CASES] = {1, 2, 65, 15};
	
	while (i < TEST_CASES)
	{
		success_cnt += TestFunc(results[i], AddOne(nums[i]), "AddOne");
        ++i;
	}
	
	printf ("In function AddOne %d / 4 success \n", success_cnt);
}

static void TestThreeBitSet(void)
{
	int nums[TEST_CASES] = {0, 11, 7, 16};
	
	ThreeBitSet(nums, TEST_CASES);
}

static void TestByteMirror(void)
{
	int i = 0;
	int success_cnt = 0;
	unsigned char nums[TEST_CASES] = {0, 1, 15, 4};
	unsigned char results[TEST_CASES] = {0, 128, 240, 32};
	
	while (i < TEST_CASES)
	{
		success_cnt += TestFunc(results[i], ByteMirror(nums[i]), "ByteMirror");
        ++i;
	}
	
	printf ("In function ByteMirror %d / 4 success \n", success_cnt);
}

static void TestByteMirrorNoLoop(void)
{
	int i = 0;
	int success_cnt = 0;
	unsigned char nums[TEST_CASES] = {0, 1, 15, 4};
	unsigned char results[TEST_CASES] = {0, 128, 240, 32};
	
	while (i < TEST_CASES)
	{
		success_cnt += TestFunc(results[i], ByteMirrorNoLoop(nums[i]), "ByteMirrorNoLoop");
        ++i;
	}
	
	printf ("In function ByteMirrorNoLoop %d / 4 success \n", success_cnt);
}

static void TestSixTwo(void)
{
	int i = 0;
	int success_cnt = 0;
	unsigned char nums[TEST_CASES] = {34, 32, 60, 0};
	unsigned char results[TEST_CASES] = {1, 0, 0, 0};
	
	while (i < TEST_CASES)
	{
		success_cnt += TestFunc(results[i], CheckSixTwo(nums[i]), "CheckCheckSixTwo");
        ++i;
	}
	
	printf ("In function Check CheckSixTwo %d / 4 success \n", success_cnt);
}

static void TestSixOrTwo(void)
{
	int i = 0;
	int success_cnt = 0;
	unsigned char nums[TEST_CASES] = {34, 2, 32, 0};
	unsigned char results[TEST_CASES] = {1, 1, 1, 0};
	
	while (i < TEST_CASES)
	{
		success_cnt += TestFunc(results[i], CheckSixOrTwo(nums[i]), "CheckSixOrTwo");
        ++i;
	}
	
	printf ("In function CheckSixOrTwo %d / 4 success \n", success_cnt);
}

static void TestFloatToBinary(void)
{
	float nums[TEST_CASES] = {23.33, 1.55, 2.50, 10.0} ;
	int i = 0;
	for(i = 0; i < TEST_CASES; ++i)
	{
		PrintFloatToBinary(nums[i]);
		printf("\n");
	}
}

