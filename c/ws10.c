#include <stdio.h>	/* printf fopen fread fwrite fclose */
#include <string.h>	/* memset strcpy 					*/
#include <assert.h> /* assert 							*/
#include <errno.h> 	/* various error codes 				*/

#include "ws10.h"


/* enum typedefs */
typedef enum {MATH , PHYSICS, LITERATURE, 
			PSYCHOLOGY, SOCIOLOGY, SPORT} subject;

/* load student from file */
state LoadStudent(student_ty *st, char *filename);
/* init student struct */
void InitStudent(student_ty *student);
/* save student to file */
state SaveStudent(student_ty *st, char *filename);

/* serialize student object and save to file */
state SaveStudent(student_ty *st, char *filename)
{
	FILE *file;
	int res = 0;
	file = fopen(filename, "wb");

	if(file == NULL)
	{
		printf("failed opening %s\n", filename);

		return FOPEN_FAIL;
	}

	res = fwrite(st, sizeof(student_ty), 1, file);

	if(res == 0)
	{
		printf("error writing to file %s\n", filename);

		return FWRITE_FAIL;
	}
	if(fclose(file) != 0)
	{
		fprintf(stderr, "Error closing file: %s", strerror(errno));

		return FCLOSE_FAIL;
	}

	return SUCCESS;
}
/* load student object from file into st  */
state LoadStudent(student_ty *st, char *filename)
{
	FILE *file;
	int res = 0;
	file = fopen(filename, "rb");

	if(file == NULL)
	{
		printf("failed loading File %s\n", filename);

		return FOPEN_FAIL;
	}

	res = fread(st, sizeof(student_ty), 1, file);
	if(res == 0)
	{
		printf("error loading student from file %s\n", filename);

		return FREAD_FAIL;
	}

	if(fclose(file) != 0)
	{
		fprintf(stderr, "Error closing file: %s", strerror(errno));
		
		return FCLOSE_FAIL;
	}

	return SUCCESS;
}












