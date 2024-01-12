#include <stdio.h>  /* printf size_t */
#include <string.h> /* memcmp strcmp */
#include <assert.h> /* assert        */

#include "ws10.h"


static void InitStudent();
static void TestSerial();
static int CompareStudents(student_ty *student1, student_ty *student2);


/* init student struct */
static void InitStudent(student_ty *student)
{
    assert(student != NULL);
    memset(student, 0, sizeof(*student));
    strcpy(student->first, "Shaul");
    strcpy(student->last, "Rosenberg");
    student->grades.sport = 88.88;
    student->grades.real.physics = 70.1;
    student->grades.real.math = 76.0;
    student->grades.human.sociology = 60.2;
    student->grades.human.psychology = 72.5;
    student->grades.human.literature = 56.4;
}


/* simple comparison for names only currently - there is no unique id */
static int CompareStudents(student_ty *student1, student_ty *student2)
{
    assert(student1 != NULL && student2 != NULL);
    if(memcmp(student1, student2, sizeof(*student1)) == 0
        && strcmp(student1->first, student2->first) == 0 
        && strcmp(student1->last, student2->last) == 0
        && student1->grades.real.math == student2->grades.real.math
        && student1->grades.real.physics == student2->grades.real.physics
        && student1->grades.human.sociology == student2->grades.human.sociology
        && student1->grades.human.psychology == student2->grades.human.psychology
        && student1->grades.human.literature == student2->grades.human.literature
        && student1->grades.sport == student2->grades.sport) return 1;
    return 0;
}

static void TestSerial()
{
    student_ty student1;
    student_ty student2;

    InitStudent(&student1);
    SaveStudent(&student1, "data.bin");
    LoadStudent(&student2, "data.bin");

    if(CompareStudents(&student1, &student2) == 1 )
    {
        printf("saving and loading the same person SUCCESS\n");
    }
}


int main()
{
    TestSerial();
    return 0;
}




