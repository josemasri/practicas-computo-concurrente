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

// Matrixes declaration
int A[N][M], B[M][Q], C[N][Q];

// Function declaration
void multiply();

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

    // Multiplying matrixes
    multiply();

    // Displaying result
    // for (int i = 0; i < N; i++)
    //     for (int j = 0; j < Q; j++)
    //         printf("C[%d][%d] = %d\n", i, j, C[i][j]);
    return 0;
}

void multiply()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < Q; ++j)
            for (int k = 0; k < M; ++k)
                C[i][j] += A[i][k] * B[k][j];
    }
}