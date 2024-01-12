#ifndef __WS3_H__
#define	__WS3_H__

#include <stddef.h>	/* size_t */




/* calculates sum of each row and return ptr */
int *MatrixRowSum(int *matrix, int *result, int row, int col);

/* list all data types and print them */
void PrintTypes();

/* copy env vars to char** buffer and print */
void PrintEnvVars(char **envp);
char **CopyEnvVars(char **envp);


/* return last alive */
int Josephus(int arr[], int size);




#endif

