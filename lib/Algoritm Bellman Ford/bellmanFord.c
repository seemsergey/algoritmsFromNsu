#include "bellmanFord.h"

PathResult* bellman_ford(const CSRGraph *graph, int start_node) {
    if (!graph || start_node < 0 || start_node >= graph->num_vertices) return NULL;

    PathResult *res = (PathResult*)malloc(sizeof(PathResult));
    res->num_vertices = graph->num_vertices;
    res->distances = (int*)malloc(sizeof(int) * graph->num_vertices);
    res->predecessors = (int*)malloc(sizeof(int) * graph->num_vertices);

    for (int i = 0; i < graph->num_vertices; i++) {
        res->distances[i] = INF_DIST;
        res->predecessors[i] = -1;
    }
    res->distances[start_node] = 0;

    // Релаксация ребер (V-1 итераций)
    for (int k = 1; k < graph->num_vertices; k++) {
        int changed = 0;
        for (int u = 0; u < graph->num_vertices; u++) {
            if (res->distances[u] == INF_DIST) continue;

            // Используем массивы из CSR структуры
            for (int j = graph->offset[u]; j < graph->offset[u + 1]; j++) {
                int v = graph->adj[j];
                int weight = graph->weights[j];

                if (res->distances[u] + weight < res->distances[v]) {
                    res->distances[v] = res->distances[u] + weight;
                    res->predecessors[v] = u;
                    changed = 1;
                }
            }
        }
        if (!changed) break; 
    }

    return res;
}

void print_path(const PathResult *result, int end_node) {
    if (!result || end_node < 0 || end_node >= result->num_vertices) return;
    
    if (result->distances[end_node] == INF_DIST) {
        printf("Путь до вершины %d недостижим.\n", end_node);
        return;
    }

    printf("Расстояние: %d | Путь: ", result->distances[end_node]);
    int cur = end_node;
    while (cur != -1) {
        printf("%d ", cur); // Для универсальности выводим числа
        cur = result->predecessors[cur];
    }
    printf("\n");
}

void free_path_result(PathResult *result) {
    if (result) {
        free(result->distances);
        free(result->predecessors);
        free(result);
    }
}