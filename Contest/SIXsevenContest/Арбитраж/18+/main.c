#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// --- СТРУКТУРЫ ДАННЫХ ---

// 1. Входные данные (ребро)
typedef struct {
    int u, v, weight;
} RawEdge;

// 2. Структура графа в формате CSR
typedef struct {
    int num_vertices;
    int num_edges;
    int *offset;  // Массив смещений (C)
    int *adj;     // Массив целей (R)
    int *weights; // Массив весов
} CSRGraph;

// 3. Результат работы алгоритма
typedef struct {
    int *dist;
    int *parent;
    int n;
} PathResult;

// --- ФУНКЦИИ ПОСТРОЕНИЯ CSR ---

// Компаратор для сортировки ребер (сначала по источнику u, потом по цели v)
int compareEdges(const void *a, const void *b) {
    RawEdge *e1 = (RawEdge *)a;
    RawEdge *e2 = (RawEdge *)b;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

CSRGraph* build_csr(int n, int m, RawEdge *raw_edges) {
    CSRGraph *graph = malloc(sizeof(CSRGraph));
    graph->num_vertices = n;
    graph->num_edges = m;
    graph->offset = calloc(n + 1, sizeof(int));
    graph->adj = malloc(m * sizeof(int));
    graph->weights = malloc(m * sizeof(int));

    // Сортируем ребра, чтобы сгруппировать их по исходной вершине u
    qsort(raw_edges, m, sizeof(RawEdge), compareEdges);

    int current_edge = 0;
    for (int i = 0; i < n; i++) {
        graph->offset[i] = current_edge;
        while (current_edge < m && raw_edges[current_edge].u == i) {
            graph->adj[current_edge] = raw_edges[current_edge].v;
            graph->weights[current_edge] = raw_edges[current_edge].weight;
            current_edge++;
        }
    }
    graph->offset[n] = m;
    return graph;
}

// --- АЛГОРИТМ БЕЛЛМАНА-ФОРДА ---

PathResult* bellman_ford(CSRGraph *graph, int start_node) {
    int n = graph->num_vertices;
    PathResult *res = malloc(sizeof(PathResult));
    res->n = n;
    res->dist = malloc(n * sizeof(int));
    res->parent = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        res->dist[i] = INF;
        res->parent[i] = -1;
    }
    res->dist[start_node] = 0;
    // Релаксация (V-1 раз)
    for (int k = 1; k < n; k++) {
        int changed = 0;
        for (int u = 0; u < n; u++) {
            if (res->dist[u] == INF) continue;

            for (int j = graph->offset[u]; j < graph->offset[u + 1]; j++) {
                int v = graph->adj[j];
                int w = graph->weights[j];
                if (res->dist[u] + w < res->dist[v]) {
                    res->dist[v] = res->dist[u] + w;
                    res->parent[v] = u;
                }
            }
        }
    }
    //проверка на цикл
    int hasCycle = 0;
    for (int u = 0; u < n; u++) {
        if (res->dist[u] == INF) continue;

        for (int j = graph->offset[u]; j < graph->offset[u + 1]; j++) {
            int v = graph->adj[j];
            int w = graph->weights[j];
            if (res->dist[u] + w < res->dist[v]) {
                res->dist[v] = res->dist[u] + w;
                res->parent[v] = u;
                hasCycle = 1;
                printf("}W}");
            }
        }
    }
    if (hasCycle) return NULL;
    return res;

}

// --- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ---

void print_path(PathResult *res, int target) {
    if (res->dist[target] == INF) {
        printf("Path to %d not exist", target);
        return;
    }
    printf("weight %d, path: ", res->dist[target]);
    int curr = target;
    while (curr != -1) {
        printf("%d ", curr);
        curr = res->parent[curr];
    }
}

void free_all(CSRGraph *g, PathResult *r) {
    free(g->offset); free(g->adj); free(g->weights); free(g);
    free(r->dist); free(r->parent); free(r);
}

// --- MAIN ---

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    RawEdge *temp_edges = malloc(M * sizeof(RawEdge));
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &temp_edges[i].u, &temp_edges[i].v, &temp_edges[i].weight);
    }

    // 1. Строим CSR
    CSRGraph *graph = build_csr(N, M, temp_edges);

    // 2. Считаем кратчайшие пути от узла 0
    int start;
    scanf("%d", &start);
    PathResult *result = bellman_ford(graph, start);
    if (result == NULL) {
        free(temp_edges);
        free_all(graph, result);
        return 0;
    }
    // 3. Вывод результата
    printf("\nRES (from %d):\n", start);
    for (int i = 0; i < N; i++) {
        printf("to %d -> ", i);
        print_path(result, i);
        printf("\n");
    }

    // Очистка памяти
    free(temp_edges);
    free_all(graph, result);

    return 0;
}