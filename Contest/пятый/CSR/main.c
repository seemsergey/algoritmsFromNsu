#include <stdio.h>
#include <stdlib.h>

// Структура для хранения ребра
typedef struct {
    int u, v;
} Edge;

int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;


    int *offset = calloc(N + 1, sizeof(int));
    int *edges = malloc(M * sizeof(int));
    Edge *temp_edges = malloc(M * sizeof(Edge));
    offset[N] = M;


    
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &temp_edges[i].u, &temp_edges[i].v);
    }

    qsort(temp_edges, M, sizeof(Edge), compareEdges);

    int count = 0;
    for (int i = 0; i < N; i++) {
        offset[i] = count;
        while (count < M && temp_edges[count].u == i) {
            edges[count] = temp_edges[count].v;
            count++;
        }
    }

    for (int i = 0; i <= N; i++) {
        printf("%d ", offset[i]);
    }
    printf("\n");
    for (int i = 0; i < M; i++) {
        printf("%d ", edges[i]);
    }
    printf("\n");

    free(temp_edges);
    free(offset);
    free(edges);

    return 0;
}