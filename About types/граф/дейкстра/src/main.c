#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lib/csr.h"


int main(void) {
    int N, S, F, M;

    if (scanf("%lld", &N) != 1) {
        return 0;
    }
    if (N < 0 || N > 5000) {
        printf("bad number of vertices\n");
        return 0;
    }

    if (scanf("%lld %lld", &S, &F) != 2) {
        printf("bad number of lines\n");
        return 0;
    }

    if (N == 0 || S < 1 || S > N || F < 1 || F > N) {
        printf("bad vertex\n");
        return 0;
    }

    // 3. Читаем M
    if (scanf("%lld", &M) != 1) {
        printf("bad number of lines\n");
        return 0;
    }

    if (M < 0 || M > N * (N - 1) / 2) {
        printf("bad number of edges\n");
        return 0;
    }

    TEdge *edges = (TEdge *) malloc(M * 2 * sizeof(TEdge));

    for (int i = 0; i < M; i++) {
        long long from, to, weight;
        int res = scanf("%lld %lld %lld", &from, &to, &weight);

        if (res == EOF || res < 3) {
            printf("bad number of lines\n");
            free(edges);
            return 0;
        }

        if (from < 1 || from > N || to < 1 || to > N) {
            printf("bad vertex\n");
            free(edges);

            return 0;
        }

        // Проверка длины ребра
        if (weight < 0 || weight > INT_MAX) {
            printf("bad length\n");
            free(edges);
            return 0;
        }

        edges[i].from = from;
        edges[i].to = to;
        edges[i].weight = weight;
        edges[i+1].from = to;
        edges[i+1].to = from;
        edges[i+1].weight = weight;
    }

    TCSRGraph *graph = BuildCSR(M, N, edges);

    /*
    int *offset; // Массив смещений
    int *adj; // Массив смежных вершин
    long long *weights; // Массив весов
     */

    int parent[N];
    long long dist[N];
    int visited[N];
    int manyWays[N];
    const int inf = -1;

    for (int i = 0; i < N; i++) {
        parent[i] = -1;
        dist[i] = inf;
        visited[i] = 0;
        manyWays[i] = 0;
    }
    dist[S] = 0;

    for (int i = 0; i < N; i++) {
        int minEdge = -1;
        long long distMin = inf;

        for (int j = 0; j < N; j++) {
            if (!visited[j] && (dist[j] < minEdge || distMin == inf)) {
                minEdge = j;
                distMin = dist[j];
            }
        }

        if (minEdge == -1) break;
        visited[minEdge] = 1;

        for (int to = graph->adj[graph->offset[minEdge]]; to < graph->adj[graph->offset[minEdge + 1]]; to++) {
            if (dist[minEdge] + graph->weights[to] < dist[to]) {
                dist[to] = dist[minEdge] + graph->weights[to];
                parent[to] = minEdge;
                manyWays[to] = manyWays[minEdge];
            } else if (dist[minEdge] + graph->weights[to] == dist[to]) {
                manyWays[to] = 1;
            }
        }

    }

    free(edges);
    return 0;
}
