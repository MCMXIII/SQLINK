#include <dlfcn.h>

int main()
{
	void* handle;
	int (*funcPointer)();
	handle = dlopen("./libN.so", RTLD_LAZY);
	funcPointer = (int (*)())dlsym(handle, "lib1Func");
	(*funcPointer)();
	funcPointer = (int (*)())dlsym(handle, "lib2Func");
	(*funcPointer)();
	funcPointer = (int (*)())dlsym(handle, "lib3Func");
	(*funcPointer)();
	dlclose(handle);
	return 0;
}