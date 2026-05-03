//
// Created by SeemS on 29.04.2026.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int **paths = (int*)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        paths[i] = (int*)malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) {
            paths[i][j] = 1;
        }
        paths[i][i] = 0;
    }
    for (int i = 0; i < M; i++) {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        paths[from][to] = weight;
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                paths[i][j] = min(paths[i][j], paths[i][k] + paths[k][j]);
            }
        }
    }

    int answ = -1, answ_cur, indx = -1;
    for (int i = 0; i < N; i++) {
        answ_cur = 0;
        for (int j = 0; j < N; j++) {
            if (paths[i][j] == -1) {
                answ_cur = -1;
                break;
            }
            answ_cur+= paths[i][j] + paths[i][j];
        }
        if (answ_cur == -1) continue;
        if (answ == -1 || answ_cur > answ) {
            answ = answ_cur;
            indx = i;
        }
    }
    printf("%d", indx);
}
