#include <stdlib.h> /* system() */
#include "ws4.h"




/* will split this later */
int main(int argc, char **argv)
{
    ChooseMethod(argc, argv);
    system("stty icanon echo");
    return 0;
}
