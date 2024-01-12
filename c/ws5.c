#include <stdio.h>	/* fopen,fclose, fprintf, fgets */
#include <stdlib.h> /*  */
#include <string.h> /* strcmp */
#include "ws5.h"

#define SIZE 256
#define UNUSED(x) (void)(x)


/**********************Ex1**************************************
* function declarations
* 
*/
typedef enum { FILE_OPEN_FAIL    = -6, 
			   WRITE_FILE_FAIL   = -5, 
			   REMOVE_FILE_FAIL  = -4, 
			   RENAME_FILE_FAIL  = -3, 
			   CLOSE_FILE_FAIL   = -2, 
			   SUCCESS           = 0, 
			   FAIL              = 1, 
			   FILE_OPEN_SUCCESS = 2 } STATE;
			   
static STATE Append(char **argv, char *str);
static STATE ExitFunc(char **str1, char *str);
static void Print(int n);
static STATE CountLines(char **argv, char *str);
static STATE RemoveFile(char **argv, char *str);
static STATE AppendToStart(char **argv, char *str);


/* comparison functions for out handle_t struct */
static int CompareFirstChar(char *str1, char *str2);
static int Compare(char *str1, char *str2);




/**************************** Ex1 Solution **********************/

static void Print(int n)
{
    printf("My Key is: %d\n", n);
}

typedef struct print_me
{
    int key;
    void (*print_ptr)(int);
} print_t;


void ArrayOfStructs()
{
	int i = 0;
    int size = 10;
    print_t print_t_array[size];
    
    for(i = 0; i < size; ++i)
    {
        print_t_array[i].key = i;
        print_t_array[i].print_ptr = &Print;
        print_t_array[i].print_ptr(print_t_array[i].key);
    }
}

/****************************Ex2***********************************/



typedef struct handle_t
{
	char description[SIZE];
	int (*cmp_func_ptr)(char *this, char *input); /* func ptr to compare input by the user to this struct operation */
	STATE (*operation_ptr)(char **argv, char*);   /* pointer to the operation function i.e : remove / append / exit / count lines */
}	handle_t; 





/* Driver program to run in main - instantiate our lookup table */
void Logger(int argc, char **argv)
{
	int i = 0;
	char choice[SIZE];
	
	handle_t handle_lut[5];
	
	if( 2 != argc )
	{
		perror("Invalid amount of arguments\n");
		exit(FAIL);
	}

	strcpy(handle_lut[0].description, "-remove");
	handle_lut[0].cmp_func_ptr = &Compare;
	handle_lut[0].operation_ptr = &RemoveFile;

	strcpy(handle_lut[1].description, "-count");
	handle_lut[1].cmp_func_ptr = &Compare;
	handle_lut[1].operation_ptr = &CountLines;

	strcpy(handle_lut[2].description, "-exit");
	handle_lut[2].cmp_func_ptr = &Compare;
	handle_lut[2].operation_ptr = &ExitFunc;

	strcpy(handle_lut[3].description, "<");
	handle_lut[3].cmp_func_ptr = &CompareFirstChar;
	handle_lut[3].operation_ptr = &AppendToStart;

	strcpy(handle_lut[4].description, "");
	handle_lut[4].cmp_func_ptr = &Compare;
	handle_lut[4].operation_ptr = &Append;
	
	printf("Operations: -count -exit -remove - < - default : Append \n");
	fgets(choice, SIZE, stdin);
	
	
	while(!Compare(choice, "-exit"))
	{
		for(i = 0; i < 5; ++i)
		{
			
			if(handle_lut[i].cmp_func_ptr(handle_lut[i].description, choice))
			{
				handle_lut[i].operation_ptr(argv, choice);
				break;
			}
		}
		printf("Choose next operation on file %s: \n", argv[1]);
		fgets(choice, SIZE, stdin);
	}
	
}

/**************************compare functions*************************************/

static int Compare(char *str1, char *str2)
{ 
	if(strncmp(str1, str2, strlen(str1)) == 0) 
	{
		return 1;
	}
	return 0;
}

static int CompareFirstChar(char *str1, char *str2)
{
	if(*str1 == *str2) 
	{
		return 1;
	}
	return 	0;
}

/************************helper functions**************************/
STATE ExitFunc(char **str1, char *str)	/* just to conform with our comparison function pointer */
{
	UNUSED(str);
	printf("Program terminated...\n");
	exit(SUCCESS);
}

/* basic append to file +a so we don't overwrite previous content */
static STATE Append(char **argv, char *str)
{
	FILE *tmp = fopen(argv[1], "a+");
	if(tmp == NULL)
	{
		perror("Failed opening file\n");
		return FILE_OPEN_FAIL;
	}
	fputs(str, tmp);
	if(fclose(tmp))
	{
		printf("fclose failed in Append \n");
		return CLOSE_FILE_FAIL;
	}
	
	return SUCCESS;
}

/* remove the file and free resources(fclose) */
static STATE RemoveFile(char **argv, char *str)
{
	UNUSED(str);
	FILE *fp = NULL;
	int ret = 0;
	fp = fopen(argv[1], "a");
	ret = remove(argv[1]);
	if(ret != 0)
	{
		printf("removing file failed\n");
		return REMOVE_FILE_FAIL;
	}
	if(!fclose(fp))
	{
		printf("%s Deleted Successfully \n", argv[1]);
		return SUCCESS;
	}
}

/* keep reading every char - count incremented every time a new line is reached.  */
static STATE CountLines(char **argv, char *str)
{
	UNUSED(str);
	FILE *tmp = fopen(argv[1], "r");
	if(tmp == NULL)
	{
		printf("Failed to open\n");
		return FILE_OPEN_FAIL;
	}
	int count = 0;
	char c;
	for(c = getc(tmp); c != EOF; c = getc(tmp))
	{
		if(c == '\n')
		{
			++count;
		}
	}
	if(fclose(tmp))
	{
		printf("fclose failed in countLines \n");
		return CLOSE_FILE_FAIL;
	}
	printf("file %s has %d lines\n", argv[1], count);
	return SUCCESS;
}

/* create a new temp file - append string , append the old file to the new one -> delete the old one and rename the new one to match old name */
static STATE AppendToStart(char **argv, char *str)
{
	/*char *file_name = argv[1];*/
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	char buffer[SIZE];
	fp1 = fopen(argv[1], "r");
	if(!fp1)
	{
		printf("failed to open fp1 in <\n");
		return FILE_OPEN_FAIL;
	}
	
	fp2 = fopen("newfile", "a+");
	if(!fp2)
	{
		printf("failed to open fp2 in <\n");
		return FILE_OPEN_FAIL;
	}
	
	fputs(str+1, fp2);
	
	/* append old file contents to new file and return new file pointer */
	while(!feof(fp1))
	{
		fgets(buffer, SIZE, fp1);
		fputs(buffer, fp2);
	}
	
	remove(argv[1]);
	rename("newfile", argv[1]);
	if(fclose(fp1))
	{
		printf("fclose failed in <\n");
		return CLOSE_FILE_FAIL;
	}
	if(fclose(fp2))
	{
		printf("fclose failed in <\n");
		return CLOSE_FILE_FAIL;
	}
	
	return SUCCESS;
} 


