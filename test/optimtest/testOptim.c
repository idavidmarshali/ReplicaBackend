#include <stdio.h>
#include <stdlib.h>

void gemm(int n, float A[n][n], float B[n][n], float C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n = 2;
    #define SIZE 1024
//    float** p = (float**) malloc((SIZE*sizeof (float*))*3);
//    for (int i = 0; i < SIZE*3; ++i) {
//        p[i] = (float*) malloc(SIZE*sizeof(float));
//    }
//    float** A = p;
//    float** B = p+(SIZE);
//    float** C = p+(SIZE*2);
    float* A[SIZE];
    float* B[SIZE];
    float* C[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        A[i] = (float*) malloc(SIZE*sizeof (float ));
        B[i] = (float*) malloc(SIZE*sizeof (float ));
        C[i] = (float*) malloc(SIZE*sizeof (float ));
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] = (float) (rand() % 100);
            B[i][j] = (float) (rand() % 100);
        }
    }
    gemm(SIZE, A, B, C);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}