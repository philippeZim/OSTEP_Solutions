#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define NUMCPUS 4  // Set the number of CPUs or threads you want to simulate
#define THRESHOLD 8  // Threshold for local counter updates before moving to global

typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    int local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int threshold;
} counter_t;

void init(counter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    for (int i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(counter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;  // Assign each thread to a CPU based on its thread ID
    pthread_mutex_lock(&c->llock[cpu]);  // Lock the local counter for the specific CPU
    c->local[cpu] += amt;

    // If the local counter exceeds the threshold, update the global counter
    if (c->local[cpu] >= c->threshold) {
        pthread_mutex_lock(&c->glock);  // Lock the global counter
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;  // Reset the local counter after updating the global counter
    }
    pthread_mutex_unlock(&c->llock[cpu]);  // Unlock the local counter for this CPU
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);
    return val;
}

// Thread function that increments the counter a specific number of times
void *increment_task(void *arg) {
    counter_t *counter = (counter_t *)arg;
    for (int i = 0; i < 250000; i++) {  // Each thread does 250,000 increments to total 1,000,000
        update(counter, pthread_self(), 1);
    }
    return NULL;
}

void measure_time(int num_threads) {
    counter_t counter;
    init(&counter, THRESHOLD);  // Initialize the counter with a threshold

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
AproxCounter:

Time taken with 1 threads: 0.01549 seconds
Time taken with 2 threads: 0.11080 seconds
Time taken with 3 threads: 0.29206 seconds
Time taken with 4 threads: 0.44019 seconds

Approximation Factor (S),Time in Seconds
1024,0.44019
512,0.75991
256,0.63132
128,0.68316
64,0.54274
32,0.64526
16,0.64657
8,0.94603
*/