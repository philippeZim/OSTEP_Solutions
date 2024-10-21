#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *a = (int *) malloc(sizeof(int) * 5);
    printf("%p\n", (void *)&a);
    return 0;
}