#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int main(void) {

    int user_size = 0;
    if(scanf("%d", &user_size) == -1) {
        perror("error using scanf");
        return -1;
    }
    vector *a = init_vector(user_size);

    for (int i = 0; i < user_size; i++) {
        append(a, i);
    }

    for (int i = 0; i < user_size; i++) {
        printf("%d\n", get(a, i));
    }
    
    free_vec(a);

    return 0;
}