#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <limits.h>

#include "../CSR/csr.h"

#define INF_DIST INT_MAX

typedef struct {
    int *distances;
    int *predecessors;
    int num_vertices;
} PathResult;

// Основная функция: принимает CSR граф и начальную вершину
PathResult* bellman_ford(const CSRGraph *graph, int start_node);

void free_path_result(PathResult *result);
void print_path(const PathResult *result, int end_node);

#endif