//
// Created by SeemS on 20.04.2026.
//

#define MAXM 500005
#define MAXN 200005

#include <stdio.h>
#include <stdlib.h>

int parent[MAXN];
int rank[MAXN];

void makeSet(int N) {
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}
// Поиск с оптимизацией (сжатие путей)
int findSet(const int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v]);
}

// Объединение по рангу
void unionSets(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (rank[a] < rank[b]) {
            parent[a] = b;
        } else if (rank[a] > rank[b]) {
            parent[b] = a;
        } else {
            parent[a] = b;
            rank[b]++;
        }
    }
}

typedef struct TEdge {
    int from, to, weight, id;
} TEdge;

TEdge Edges[MAXM];

int compareEdges(const void *a, const void *b) {
    const TEdge *edgeA = (TEdge *) a;
    const TEdge *edgeB = (TEdge *) b;

    if (edgeA->weight < edgeB->weight) return -1;
    if (edgeA->weight > edgeB->weight) return 1;
    return 0;
}

int main(void) {
    int answ[MAXM] = {0};
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &Edges[i].from, &Edges[i].to, &Edges[i].weight);
        Edges[i].id = i;
    }
    qsort(Edges, M, sizeof(TEdge), compareEdges);

    makeSet(N);


    for (int i = 0; i < M; i++) {
        if (i + 1 < M && Edges[i].weight == Edges[i + 1].weight) {
            int j = i;
            while (j < M && Edges[i].weight == Edges[j].weight) {
                if (findSet(Edges[j].from) != findSet(Edges[j].to)) {
                    answ[Edges[j].id] = 1;
                } else {
                    answ[Edges[j].id] = 0;
                }
                j++;
            }
            for (int k = i; k < j; k++) {
                unionSets(Edges[k].from, Edges[k].to);
            }

            i = j - 1;
        } else {
            if (findSet(Edges[i].from) != findSet(Edges[i].to)) {
                answ[Edges[i].id] = 1;
                unionSets(Edges[i].from, Edges[i].to);
            } else {
                answ[Edges[i].id] = 0;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        printf("%d", answ[i]);
    }
}
