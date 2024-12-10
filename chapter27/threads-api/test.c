#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void* func(void* arg) {
    int arg_int = (int) arg;
    int x = arg_int * 2;
    return (void*) x;
}

int main(void) {
    int x = 100;
    void *test = malloc(sizeof(void *));
    test = func((void*)x);
    printf("%d\n",(int) test);
}