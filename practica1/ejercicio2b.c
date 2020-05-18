#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Constanats
#define MAX_INT 10
// Matrixes size
#define N 4000
#define M 4000
#define Q 4000
#define NUM_THREADS 8

// Matrixes declaration
int A[N][M], B[M][Q], C[N][Q];

// Function declaration
void *multiply();

int main(int argc, char const *argv[])
{
    // Initilizing random seed
    srand(time(NULL));
    // Initialize matrixes randomly
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            A[i][j] = rand() % MAX_INT;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < Q; j++)
            B[i][j] = rand() % MAX_INT;

    // Printing matrixes
    // for (int i = 0; i < N; i++)
    //     for (int j = 0; j < M; j++)
    //         printf("A[%d][%d] = %d\n", i, j, A[i][j]);

    // for (int i = 0; i < M; i++)
    //     for (int j = 0; j < Q; j++)
    //         printf("B[%d][%d] = %d\n", i, j, B[i][j]);

    // Creating thread array
    pthread_t threads[NUM_THREADS];
    // Variable for the return code
    // of creating the thread
    int rc;
    // Launching threads
    // Creating threads with sum function
    for (long t = 0; t < NUM_THREADS; t++)
    {
        // printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, multiply, (void *)t);
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

    // Displaying result
    // for (int i = 0; i < N; i++)
    //     for (int j = 0; j < Q; j++)
    //         printf("C[%d][%d] = %d\n", i, j, C[i][j]);
    return 0;
}

void *multiply(void *threadid)
{
    long tid = (long)threadid;
    // Cells to compute
    long cellsToCompute = N * Q / NUM_THREADS;
    long start = cellsToCompute * tid;
    long end = start + cellsToCompute;

    long row;
    long col;

    for (int k = start; k < end; k++)
    {
        row = k / cellsToCompute;
        col = k % cellsToCompute;
        // One cell calculation
        for (int i = 0; i < M; ++i)
            C[row][col] += A[row][i] * B[i][col];
    }
}