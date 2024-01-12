#ifndef __WS11_H__
#define __WS11_H__

/* same as CheckEndian without additional var */
#define IS_LITTLE_END (char)((int)1) ? 1 : 0

/* returns num as string */
char* Itoa(int num, char* str, int base);

/* return string str as integer */
int Atoi(char *str, int base);

/* return 1 if small endian or 0 if Big endian */
int IsLittleEndian(void);

/* will print whatever char is present in A and B but not C (once) */
void InFirstAndSecondButNotThird(char A[], char B[], char C[]);


#endif /* __WS11_H__ */



