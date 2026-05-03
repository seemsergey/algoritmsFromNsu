#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005
#define MAXM 20005
#define INF_LL 1000000000000000000LL

// csr graph
int offset[MAXN + 1];
int adj[MAXM];
int weights[MAXM];

long long dist[MAXN];
int parent[MAXN];

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
            adj[current_edge] = raw_edges[current_edge].v;
            weights[current_edge] = raw_edges[current_edge].weight;
            current_edge++;
        }
    }
    offset[n] = m;
}

int bellman_ford(int n, int start_node) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF_LL;
        parent[i] = -1;
    }
    dist[start_node] = 0;

    // Релаксация (V-1 раз)
    for (int k = 1; k < n; k++) {
        int changed = 0;
        for (int u = 0; u < n; u++) {
            if (dist[u] == INF_LL) continue;

            for (int j = offset[u]; j < offset[u + 1]; j++) {
                int v = adj[j];
                int w = weights[j];
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    changed = 1;
                }
            }
        }
        if (!changed) break; // Оптимизация: если ничего не меняется, выходим раньше
    }

    // Проверка на отрицательный цикл
    for (int u = 0; u < n; u++) {
        if (dist[u] == INF_LL) continue;
        for (int j = offset[u]; j < offset[u + 1]; j++) {
            int v = adj[j];
            int w = weights[j];
            if (dist[u] + w < dist[v]) {
                return -1; // Найден цикл
            }
        }
    }
    return 0;
}

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    RawEdge *temp_edges = malloc(M * sizeof(RawEdge));
    for (int i = 0; i < M; i++) {
        // Предполагаем 0-индексацию. Если в вводе 1-индексация, используйте temp_edges[i].u - 1
        scanf("%d %d %d", &temp_edges[i].u, &temp_edges[i].v, &temp_edges[i].weight);
    }

    int start;
    if (scanf("%d", &start) != 1) start = 0;

    buildCsr(N, M, temp_edges);

    int result = bellman_ford(N, start);

    if (result == -1) {
        printf("-1");
    } else {
        for (int i = 0; i < N; i++) {
            if (dist[i] == INF_LL) {
                printf("INF");
            } else {
                printf("%lld", dist[i]);
            }
            if (i < N - 1) printf(" ");
        }
    }
    free(temp_edges);
    return 0;
}