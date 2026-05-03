//
// Created by SeemS on 08.04.2026.
//
//топологическая сортировка -> куча -> нужен порядок -> куча с приоритетом
// надо: массив имён, массив кол-ва зависимостей, хэш-таблица зависимостей(кол-во зав., сам список смежностей, сколько сейчас эл-тов),
//          куча с приоритетом(по именам), размер кучи, ф-ии кучи: вставка, удаление, топологическая сортировка через Кана,
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 1005
#define maxName 64

char fileName[maxN][maxName];
int inDegree[maxN];
int *adj[maxN];
int adjN[maxN];
int adjCountMax[maxN];
int Heap[maxN];
int heapSize = 0;

void sortHeap() {
    int i = heapSize;
    while (i > 1) {
        if (strcmp(fileName[Heap[i]], fileName[Heap[i - 1]]) > 0) {
            int temp = Heap[i];
            Heap[i] = Heap[i - 1];
            Heap[i - 1] = temp;
            i--;
        } else {
            break;
        }
    }
}

void push(int num) {
    heapSize++;
    Heap[heapSize] = num;
    sortHeap();
}

int pop() {
    if (heapSize == 0) return -1;
    return Heap[heapSize--];
}

int find_id(int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(fileName[i], name) == 0)
            return i;
    }
    return -1;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int depsCount[maxN];
    char **deps[maxN];

    for (int i = 0; i < N; i++) {
        scanf("%s", fileName[i]);
        scanf("%d", &depsCount[i]);

        deps[i] = malloc(depsCount[i] * sizeof(char*));
        for (int j = 0; j < depsCount[i]; j++) {
            deps[i][j] = malloc(maxName);
            scanf("%s", deps[i][j]);
        }

        adjN[i] = 0;
        adjCountMax[i] = 10;
        adj[i] = malloc(adjCountMax[i] * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        inDegree[i] = depsCount[i];
        for (int j = 0; j < depsCount[i]; j++) {
            int from = find_id(N, deps[i][j]);
            int to = i;

            if (adjN[from] == adjCountMax[from]) {
                adjCountMax[from] *= 2;
                adj[from] = realloc(adj[from], adjCountMax[from] * sizeof(int));
            }
            adj[from][adjN[from]++] = to;
        }
    }

    for (int i = 0; i < N; i++) {
        if (inDegree[i] == 0) {
            push(i);
        }
    }

    int topoSort[maxN];
    int countTopoSort = 0;

    while (heapSize > 0) {
        int u = pop();
        topoSort[countTopoSort++] = u;

        for (int i = 0; i < adjN[u]; i++) {
            int v = adj[u][i];
            inDegree[v]--;
            if (inDegree[v] == 0) {
                push(v);
            }
        }
    }

    if (countTopoSort == N) {
        for (int i = 0; i < N; i++) {
            printf("%s\n", fileName[topoSort[i]]);
        }
    } else {
        printf("-1\n");
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < depsCount[i]; j++) free(deps[i][j]);
        free(deps[i]);
        free(adj[i]);
    }

    return 0;
}