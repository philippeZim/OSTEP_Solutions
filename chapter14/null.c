#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *a = NULL;
    printf("%d\n", *a);
    free(a);
    return 0;
}