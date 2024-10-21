#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int last;
    int size;
} vector;

vector *init_vector() {
    vector *v = (vector *) malloc(sizeof(vector));
    if (v == NULL) {
        perror("error using malloc in init_vector");
        exit(1);
    }
    v->arr = (int *)malloc(sizeof(int)*100);
    if (v->arr == NULL) {
        perror("error using malloc in init_vector arr");
        exit(1);
    }
    v->size = 100;
    v->last = 0;
    return v;
}

void append(vector *v, int x) {
    if (v->last == v->size) {
        v->arr = (int *)realloc(v->arr, sizeof(int)*(size_t)(v->size*2));
        if (v->arr == NULL) {
            perror("error using malloc in append on arr");
            exit(1);
        }
        v->size *= 2;
    }
    v->arr[v->last] = x;
    v->last++;
}

int get(vector *v, int index) {
    if (index < 0 || index >= v->last) {
        perror("Index out of bounds in vector");
        exit(1);
    }
    return v->arr[index];
}

void free_vec(vector *v) {
    free(v->arr);
    free(v);
}