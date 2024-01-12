#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */
#include <stdlib.h> /* system(tty)   */
#include "ws4.h"



static int flag = 1;

static void IfElse(void);
static void SwitchCase(void);
static void LookUp(void);



static void EscPressed()
{
	system("stty icanon echo");
	flag = 0;
}


static void PrintA()
{
    puts("A was pressed! \n");
}

static void PrintT()
{
    puts("T was pressed! \n");
}

static void PrintNothing()
{

}




void (*print_char_t)(void) = &PrintT;
void (*print_char_a)(void) = &PrintA;
void (*print_nothing)(void)= &PrintNothing;



int ChooseMethod(int argc, char **argv)
{
	system("stty -icanon -echo");
    if(2 != argc)
    {
        printf("invalid amount of arguments... Aborting\n");
        return 1;
    }
	if(strcmp(argv[1], "1") == 0)
	{
		printf("You chose IfElse: waiting for key press...\n");
		IfElse();
		return 0;
	}
	else if(strcmp(argv[1], "2") == 0)
	{
		printf("You chose Switch Case: waiting for key press...\n");
		SwitchCase();
		return 0;
	}
	else if(strcmp(argv[1], "3") == 0)
	{
		printf("You chose LookUpTable: waiting for key press...\n");
		LookUp();
		return 0;
	}
    else
    {
        printf("No valid input - Aborting...");
        return 1;
    }
	return 0;
}

static void IfElse(void)
{
    char my_input;
    do
    {
        my_input = getchar();
        if(my_input == 'T')
        {
            printf("T was pressed! \n");
        }
        else if(my_input == 'A')
        {
            printf("A was pressed! \n");
        }
        else if(my_input == 27)
        {
        	flag = 0;
        }

    } while (flag);
    
  
}   


static void SwitchCase(void)
{
    char my_input;
    do
    {
        my_input = getchar();
        switch(my_input)
        {
            case 'T':
            printf("T was pressed! \n");
            break;
            
            case 'A':
            printf("A was pressed! \n");
            break;
         
            case 27:
            flag = 0;
            
            default:
            break;
        }  /* code */
    } while (flag);
}


static void LookUp(void)
{
    void (*ascii_table[256])(void);
    char my_input;
    int i = 0;
    for(i = 0; i < 256; ++i)
    {
        if(i == 84)
        {
            ascii_table[i] = print_char_t;
        }
        else if(i == 65)
        {
            ascii_table[i] = print_char_a;
        }
        else if(i == 27)
        {
        	ascii_table[i] = &EscPressed;
        }
        else
        {
            ascii_table[i] = print_nothing;
        }
    }


    do
    {
        my_input = getchar();
       	ascii_table[my_input]();
    } while (flag);
    

}








