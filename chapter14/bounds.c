#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *data = (int *) malloc(sizeof(int)*100);
    data[100] = 0;
    printf("%d\n", data[100]);
    return 0;
}