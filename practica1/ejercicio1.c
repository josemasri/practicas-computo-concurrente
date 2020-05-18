#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10
#define SIZE_ARR 1000

// Global variables declaration
// Accesible by anyone
int arr[SIZE_ARR];
int totalSum = 0;

// Functions declaration
void *sum(void *threadid);

int main(int argc, char *argv[])
{
    // Creating thread array
    pthread_t threads[NUM_THREADS];
    // Variable for the return code
    // of creating the thread
    int rc;
    // Initializing array
    for (int i = 0; i < SIZE_ARR; i++)
        arr[i] = i + 1;
    // Creating threads with sum function
    for (long t = 0; t < NUM_THREADS; t++)
    {
        // printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, sum, (void *)t);
        // Error handling
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    // Waiting for all threads to end
    for (long t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL);
    // Outputing the result
    printf("Sum = %d\n", totalSum);
    // Outputing the computed reslt
    printf("Expected Sum = %d\n", (SIZE_ARR * (SIZE_ARR + 1)) / 2);
    // Exiting principal thread
    pthread_exit(NULL);
}

// Sum function for threads
// Argument is the thread id
void *sum(void *threadid)
{
    long tid;
    int chunk_size = SIZE_ARR / NUM_THREADS;
    tid = (long)threadid;
    // printf("Hello World! It's me, thread #%ld!\n", tid);
    for (int i = tid * chunk_size; i < (tid * chunk_size) + chunk_size; i++)
        totalSum = totalSum + arr[i];
    pthread_exit(NULL);
}