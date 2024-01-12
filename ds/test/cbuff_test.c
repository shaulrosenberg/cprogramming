#include "cbuff.h" 
#include "tests.h" 

static void TestCB(void); 


int main(void)
{
	TestCB();

	PASS;

	return 0;
}

void TestCB(void)
{
	char array[] = {"hello"};
	char array_dest[6]; 
	size_t capacity = sizeof(array) - 1;
	/* create the c buffer */ 
	c_buff_ty *c_buffer = CBuffCreate(capacity);
	
	/* expected empty c buffer */ 
	TEST("CBufferIsEmpty", CBuffIsEmpty(c_buffer), 1);
	
	/* expected 0 size */ 
	TEST("CBuffSize", CBuffSize(c_buffer), 0);
	
	TEST("CBFreeSpace", CBuffFreeSpace(c_buffer), capacity);
	
	TEST("CBuffWrite", CBuffWrite(c_buffer, array, 3), 3);
	
	/* expected 3 size */ 
	TEST("CBuffSize", CBuffSize(c_buffer), 3);
	
	/* expected non empty c buffer */ 
 	TEST("CBufferIsEmpty", CBuffIsEmpty(c_buffer), 0);
 	
	/* read 2 / 3 chars */ 
	TEST("CBuffRead", CBuffRead(c_buffer, array_dest, 2), 2);
	
	/* expected 1 size */ 
	TEST("CBuffSize", CBuffSize(c_buffer), 1);
	
	/* expected non empty c buffer */ 
	TEST("CBufferIsEmpty", CBuffIsEmpty(c_buffer), 0); 
	TEST("CBFreeSpace", CBuffFreeSpace(c_buffer), capacity -1);
	
	/* read 3 / 1 chars -> reads only 1 */ 
	TEST("CBuffRead", CBuffRead(c_buffer, array_dest, 3), 1);
	
	
	/* expected empty c buffer */ 
	TEST("CBufferIsEmpty", CBuffIsEmpty(c_buffer), 1);
	
	TEST("CBFreeSpace", CBuffFreeSpace(c_buffer), capacity);
	TEST("CBuffSize", CBuffSize(c_buffer), 0);
	
	/* total size = 4 */
	TEST("CBuffWrite", CBuffWrite(c_buffer, array, 4), 4);
	TEST("CBuffSize", CBuffSize(c_buffer), 4);
	
	/* read 4 / 4 chars  */ 
	TEST("CBuffRead", CBuffRead(c_buffer, array_dest, 4), 4);
	TEST("CBuffSize", CBuffSize(c_buffer), 0);
	
	/* expected empty c buffer */ 
	TEST("CBufferIsEmpty", CBuffIsEmpty(c_buffer), 1);
	
	/* free c buffer memory */ 
	CBuffDestroy(c_buffer);
}
