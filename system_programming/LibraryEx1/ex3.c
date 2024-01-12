#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

typedef void (*print_int)(int);

int main() {
    /* Declare a handle for the library and a function pointer */
    void *handle;
    char *error;
    print_int myFoo;

    /* Use dlopen() to open the library */
    handle = dlopen("libfoo.so", RTLD_LAZY);
    if (!handle) {
        /* If the handle is NULL, dlopen failed.
        * Print the error message and exit
        */
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    /* Clear any existing error */
    dlerror();

    /* Use dlsym() to look up the symbol "Foo" */
    myFoo = (void (*)(int)) dlsym(handle, "Foo");

    /* Check for errors */
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    /* Print the result of calling the function */
    myFoo(99);

    /* Close the library using dlclose() */
    dlclose(handle);

    return 0;
}