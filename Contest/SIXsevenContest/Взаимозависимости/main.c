#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 500005

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int *offset;
    int *edges;
} CSRGraph;

int visited[MAXN];
int post_order[MAXN];
int post_ptr = 0;
int scc[MAXN];
int current_scc = 0;
int stack[MAXN];
int edge_ptr[MAXN]; // Вынесли в глобальную область

void dfs1_iter(int start_node, CSRGraph *g) {
    int top = 0;
    stack[top++] = start_node;
    visited[start_node] = 1;

    while (top > 0) {
        int u = stack[top - 1];
        int found = 0;

        for (int i = edge_ptr[u]; i < g->offset[u + 1]; i++) {
            int v = g->edges[i];
            edge_ptr[u] = i + 1; // Запоминаем, на каком ребре остановились
            if (!visited[v]) {
                visited[v] = 1;
                stack[top++] = v;
                found = 1;
                break;
            }
        }

        if (!found) {
            post_order[post_ptr++] = u;
            top--;
        }
    }
}

void dfs2_iter(int start_node, CSRGraph *g, int id) {
    int top = 0;
    stack[top++] = start_node;
    visited[start_node] = 1;
    scc[start_node] = id;

    while (top > 0) {
        int u = stack[--top];
        for (int i = g->offset[u]; i < g->offset[u + 1]; i++) {
            int v = g->edges[i];
            if (!visited[v]) {
                visited[v] = 1;
                scc[v] = id;
                stack[top++] = v;
            }
        }
    }
}

int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

void buildCsr(int n, int m, Edge *raw_edges, CSRGraph *graph) {
    qsort(raw_edges, m, sizeof(Edge), compareEdges);
    graph->offset = malloc((n + 1) * sizeof(int));
    graph->edges = malloc(m * sizeof(int));
    int current_edge = 0;
    for (int i = 0; i < n; i++) {
        graph->offset[i] = current_edge;
        while (current_edge < m && raw_edges[current_edge].u == i) {
            graph->edges[current_edge] = raw_edges[current_edge].v;
            current_edge++;
        }
    }
    graph->offset[n] = m;
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    Edge *raw = malloc(m * sizeof(Edge));
    Edge *rawT = malloc(m * sizeof(Edge));

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &raw[i].u, &raw[i].v);
        // Используем 0-индексацию как во входных данных примера
        rawT[i].u = raw[i].v;
        rawT[i].v = raw[i].u;
    }

    CSRGraph G, GT;
    buildCsr(n, m, raw, &G);
    buildCsr(n, m, rawT, &GT);

    // Подготовка для DFS1
    for(int i = 0; i < n; i++) edge_ptr[i] = G.offset[i];
    memset(visited, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1_iter(i, &G);
    }

    // DFS2
    memset(visited, 0, sizeof(int) * n);
    for (int i = n - 1; i >= 0; i--) {
        int u = post_order[i];
        if (!visited[u]) {
            dfs2_iter(u, &GT, current_scc++);
        }
    }

    int *sccSize = calloc(current_scc, sizeof(int));
    for (int i = 0; i < n; i++) sccSize[scc[i]]++;

    // Списки смежности для вывода (идем с конца в начало для сохранения порядка)
    int *head = malloc(current_scc * sizeof(int));
    memset(head, -1, current_scc * sizeof(int));
    int *next = malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--) {
        int id = scc[i];
        next[i] = head[id];
        head[id] = i;
    }

    int goodCount = 0;
    for (int i = 0; i < current_scc; i++) if (sccSize[i] > 1) goodCount++;

    printf("%d\n", goodCount);
    for (int i = 0; i < current_scc; i++) {
        if (sccSize[i] > 1) {
            printf("%d", sccSize[i]);
            int curr = head[i];
            while (curr != -1) {
                printf(" %d", curr);
                curr = next[curr];
            }
            printf("\n");
        }
    }

    int q;
    if (scanf("%d", &q) == 1) {
        for (int i = 0; i < q; i++) {
            int a, b;
            if (scanf("%d %d", &a, &b) != 2) break;
            if (a >= 0 && a < n && b >= 0 && b < n && scc[a] == scc[b]) printf("1");
            else printf("0");
        }
        printf("\n");
    }

    // Чистка памяти (опционально)
    free(raw); free(rawT); free(sccSize); free(head); free(next);
    return 0;
}