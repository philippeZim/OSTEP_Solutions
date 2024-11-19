#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a[100];
    /*
    for (int i = 0; i < 100; i++) {
        printf("%d\n", a[i]);
    }
    */

    int *b = (int *)malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        b[i] = -1;
    }
    free(b);
    int *c = (int *) malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        printf("%d\n", c[i]);
    }
    return 0;
}