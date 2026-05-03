//
// Created by SeemS on 03.05.2026.
//
#include <stdlib.h>

#define MAXN 200005
#define MAXM 500005

// csr graph
int offset[MAXN + 1];
int edges[MAXM];

typedef struct {
    int u, v, weight;
} RawEdge;

int compareEdges(const void *a, const void *b) {
    RawEdge *e1 = (RawEdge *)a;
    RawEdge *e2 = (RawEdge *)b;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

void buildCsr(int n, int m, RawEdge *raw_edges) {
    // Сортируем ребра по исходной вершине u
    qsort(raw_edges, m, sizeof(RawEdge), compareEdges);

    for (int i = 0; i <= n; i++) offset[i] = 0;

    int current_edge = 0;
    for (int i = 0; i < n; i++) {
        offset[i] = current_edge;
        while (current_edge < m && raw_edges[current_edge].u == i) {
            edges[current_edge] = raw_edges[current_edge].v;
            weights[current_edge] = raw_edges[current_edge].weight;
            current_edge++;
        }
    }
    offset[n] = m;
}

int main(void) {

}