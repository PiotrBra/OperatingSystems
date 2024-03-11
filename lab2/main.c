#include <stdio.h>

#ifdef DLL
#include <dlfcn.h>
#else
extern int test_collatz_convergence(int input, int max_iter);
#endif


int main(int argc, char** argv) {
#ifdef DLL
    void* handle = dlopen("./libcollatz.so", RTLD_LAZY);
    if (!handle) {
        printf("nie udalo sie otworzyc libcollatz.so!\n");
        return -1;
    }

    int (*test_collatz_convergence)(int, int);
    test_collatz_convergence = dlsym(handle, "test_collatz_convergence");
    if (dlerror() != 0) {
        printf("nie udalo sie zaladowac test_collatz_convergence() \n");
        return -2;
    }
#endif
    printf("test\n");
    printf("input = 1 max_iter = 5 , %d\n", test_collatz_convergence(1, 5));
    printf("input = 123 max_iter = 100 , %d\n", test_collatz_convergence(123, 100));
    printf("input =  420 max_iter = 10 , %d\n", test_collatz_convergence(420, 10));
    printf("input = 3434 max_iter = 100 , %d\n", test_collatz_convergence(3434, 100));
    printf("input = 99999 max_iter = 100 , %d\n", test_collatz_convergence(99999, 100));

    return 0;
}