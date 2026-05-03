//
// Created by SeemS on 29.11.2025.
//
#include <stdio.h>
#include <stdlib.h>



void MakeSet(int x) {
    p[x] = x;
    rank[x] = 0;
}

int FindSet(int x) {
    if (x == p[x])
        return x;
    return p[x] = FindSet(p[x]);

}

void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);
    if (x == y) return;

    if (rank[x] < rank[y]) {
        p[x] = y;
    } else if (rank[x] > rank[y]) {
        p[y] = x;
    } else {
        p[x] = y;
        rank[y]++;
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int p[N*M];
    int rank[N];
    int **field = (int**)malloc(N * sizeof(int*));
    for (int i = 0 ; i < N ; ++i) {
        field[i] = (int*)malloc(M * sizeof(int));
        for (int j = 0 ; j < M ; ++j) {
            scanf("%d", &field[i][j]);
            MakeSet(i * M + j);
        }
    }



}
