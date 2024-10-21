#include <stdlib.h>
#include <stdio.h>
int main(void) {
    int *arr = (int *)malloc(sizeof(int)*10);
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    
    //free(&arr[5]);
    for (size_t i = 0; i < 10; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}