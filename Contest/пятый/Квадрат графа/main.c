//
// Created by SeemS on 24.03.2026.
//

#include <stdio.h>
#include <stdlib.h>

void findAllSecond(int *A, int *B, int N, int start, int second) {
    for (int j = 0; j < N; j++) {
        if (A[second * N + j] == 1) {
            B[start * N + j] = 1;
        }
    }
}


int main(void) {
    int N;
    scanf("%d", &N);
    int *A = calloc(N*N, sizeof(int));
    int *B = calloc(N*N, sizeof(int));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i* N + j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i* N + j] == 1) {
                findAllSecond(A, B, N, i, j);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", B[i* N + j]);
        }
        printf("\n");
    }
    free(A);
    free(B);
}
