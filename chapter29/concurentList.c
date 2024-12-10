#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

// basic list structure (one used per list)
typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L) {
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}


int List_Insert(list_t *L, int key) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return -1;
    }
    new->key = key;
    // just lock critical section
    pthread_mutex_lock(&L->lock);
    new->next = L->head;
    L->head = new;
    pthread_mutex_unlock(&L->lock);
    return 0; // success
}

int List_Lookup(list_t *L, int key) {
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv; // now both success and failure
}

void *work(void * arg) {
    int limit = 40000;
    list_t * lp = (list_t*)arg;
    for (int i = 0; i <limit; i++) {
        List_Insert(lp, 1);
    }
}

#define BUCKETS (101)

typedef struct __hash_t {
    list_t lists[BUCKETS];
} hash_t;

void Hash_Init(hash_t *H) {
    int i;
    for (i = 0; i < BUCKETS; i++)
        List_Init(&H->lists[i]);
}

int Hash_Insert(hash_t *H, int key) {
    return List_Insert(&H->lists[key % BUCKETS], key);
}

int Hash_Lookup(hash_t *H, int key) {
    return List_Lookup(&H->lists[key % BUCKETS], key);
}

void *work2(void * arg) {
    int limit = 10000;
    hash_t * lp = (hash_t*)arg;
    for (int i = 0; i <limit; i++) {
        Hash_Insert(lp, rand());
    }
}


int main(void) {
    srand(time(0));
    /*
    list_t *my_list = malloc(sizeof(list_t));
    if (!my_list) return -1;
    List_Init(my_list);



    int num_threads = 4;
    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, work, (void *)my_list);
    }

    


    // Wait for all threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    */

    hash_t *my_hash = malloc(sizeof(hash_t));
    if (!my_hash) return -1;
    Hash_Init(my_hash);



    int num_threads = 4;
    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, work2, (void *)my_hash);
    }

    


    // Wait for all threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
}


/*
concurent List:
time in s, number of inserts
0.025,10000
0.036,20000
0.050,30000
0.103,40000

concurent Hash table
time in s, number of inserts

0.084,40000
0.066,30000
0.052,20000
0.024,10000
*/