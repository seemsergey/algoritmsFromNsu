#include "csr.h"
#include <string.h>

// Компаратор для qsort: сначала по u, потом по v
static int compare_raw_edges(const void *a, const void *b) {
    const RawEdge *e1 = (const RawEdge *) a;
    const RawEdge *e2 = (const RawEdge *) b;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

CSRGraph *build_csr(int num_vertices, int num_edges, RawEdge *edges) {
    CSRGraph *graph = (CSRGraph *) malloc(sizeof(CSRGraph));
    graph->num_vertices = num_vertices;
    graph->num_edges = num_edges;

    graph->offset = (int *) calloc(num_vertices + 1, sizeof(int));
    graph->adj = (int *) malloc(num_edges * sizeof(int));
    graph->weights = (int *) malloc(num_edges * sizeof(int));

    // 1. Сортируем входные ребра по исходной вершине (u)
    qsort(edges, num_edges, sizeof(RawEdge), compare_raw_edges);

    // 2. Заполняем массивы adj и weights, и вычисляем смещения
    int current_edge = 0;
    for (int i = 0; i < num_vertices; i++) {
        graph->offset[i] = current_edge;
        while (current_edge < num_edges && edges[current_edge].u == i) {
            graph->adj[current_edge] = edges[current_edge].v;
            graph->weights[current_edge] = edges[current_edge].weight;
            current_edge++;
        }
    }
    // Последний элемент всегда равен количеству ребер
    graph->offset[num_vertices] = num_edges;

    return graph;
}

void print_csr_info(const CSRGraph *graph) {
    printf("Offsets (C): ");
    for (int i = 0; i <= graph->num_vertices; i++) printf("%d ", graph->offset[i]);

    printf("\nAdjacency (R): ");
    for (int i = 0; i < graph->num_edges; i++) printf("%d ", graph->adj[i]);

    printf("\nWeights: ");
    for (int i = 0; i < graph->num_edges; i++) printf("%d ", graph->weights[i]);
    printf("\n");
}

void free_csr(CSRGraph *graph) {
    if (graph) {
        free(graph->offset);
        free(graph->adj);
        free(graph->weights);
        free(graph);
    }
}