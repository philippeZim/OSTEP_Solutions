#include <stdlib.h>
#include "vector.h"

int main(void) {
    vector *a = init_vector();

    for (int i = 0; i < 500; i++) {
        append(a, i);
    }

    for (int i = 0; i < 500; i++) {
        printf("%d\n", get(a, i));
    }
    
    free_vec(a);

    return 0;
}