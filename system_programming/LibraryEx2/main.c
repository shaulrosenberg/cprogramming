#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#include "ex1.h"

typedef void (*printFunc)();

int main()
{
	void *handle1 = NULL;
	void *handle2 = NULL;

	printFunc func1;
	printFunc func2;

	handle1 = dlopen("dyn1.so", RTLD_LAZY);
	handle2 = dlopen("dyn2.so", RTLD_LAZY);

	func1 = (printFunc)dlsym(handle1, "Foo");
	func2 = (printFunc)dlsym(handle2, "Foo2");

	func1();
	func2();



	return 0;
}