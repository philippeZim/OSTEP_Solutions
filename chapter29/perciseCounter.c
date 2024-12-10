#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}

// Thread function that increments the counter a specific number of times
void *increment_task(void *arg) {
    counter_t *counter = (counter_t *)arg;
    for (int i = 0; i < 250000; i++) {  // Each thread does 250,000 increments to total 1,000,000
        increment(counter);
    }
    return NULL;
}

void measure_time(int num_threads) {
    counter_t counter;
    init(&counter);

    // Create an array to hold the threads
    pthread_t threads[num_threads];

    // Record the start time
    clock_t start = clock();

    // Create the threads
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, increment_task, (void *)&counter);
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Record the end time
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Output the results
    printf("Time taken with %d threads: %.5f seconds\n", num_threads, elapsed_time);
}

int main() {
    // Measure time for 1,000,000 increments with 1, 2, 3, and 4 threads
    for (int num_threads = 1; num_threads <= 4; num_threads++) {
        measure_time(num_threads);
    }

    return 0;
}


/*
Percise Counter:

Time taken with 1 threads: 0.00698 seconds
Time taken with 2 threads: 0.03794 seconds
Time taken with 3 threads: 0.15413 seconds
Time taken with 4 threads: 0.37798 seconds
*/