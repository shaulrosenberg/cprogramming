#ifndef __WS10_H__
#define __WS10_H__

#define BUFFER_SIZE 50

/* state enum */
typedef enum {SUCCESS, FAIL, FWRITE_FAIL, 
			FREAD_FAIL, FOPEN_FAIL, FCLOSE_FAIL} state;
/* struct typedef */

typedef struct human
{
	float sociology;
	float psychology;
	float literature;
} human_ty;


typedef struct real
{
	float physics;
	float math;
} real_ty;

typedef struct grades
{
	human_ty human;
	real_ty real;
	float sport;
} grades_ty;


typedef struct student
{
	char first[BUFFER_SIZE];
	char last[BUFFER_SIZE];
	grades_ty grades;
} student_ty;


/* Load student info from file returns SUCCESS(0) on success or FAIL(1) on  fail */
state LoadStudent(student_ty *st, char *filename);

/* save student to file returns SUCCESS(0) on success or FAIL(1) on  fail */
state SaveStudent(student_ty *st, char *filename);




#endif /* __WS10_H__ */




