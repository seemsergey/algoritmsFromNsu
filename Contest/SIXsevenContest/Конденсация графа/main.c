#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 500005

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int offset[MAXN + 1];
    int edges[MAXM];
} CSRGraph;

CSRGraph G, GT;
int visited[MAXN];
int post_order[MAXN];
int post_ptr = 0;
int scc[MAXN];
int current_scc = 0;

int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

void buildCsr(int n, int m, Edge *raw_edges, CSRGraph *graph) {
    qsort(raw_edges, m, sizeof(Edge), compareEdges);
    for (int i = 0; i <= n; i++) graph->offset[i] = 0;
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

void dfs1(int u) {
    visited[u] = 1;
    for (int i = G.offset[u]; i < G.offset[u + 1]; i++) {
        int v = G.edges[i];
        if (!visited[v]) dfs1(v);
    }
    post_order[post_ptr++] = u;
}

void dfs2(int u, int id) {
    visited[u] = 1;
    scc[u] = id;
    for (int i = GT.offset[u]; i < GT.offset[u + 1]; i++) {
        int v = GT.edges[i];
        if (!visited[v]) dfs2(v, id);
    }
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    Edge *raw = malloc(m * sizeof(Edge));
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &raw[i].u, &raw[i].v);
    }

    buildCsr(n, m, raw, &G);

    for (int i = 0; i < m; i++) {
        int tmp = raw[i].u;
        raw[i].u = raw[i].v;
        raw[i].v = tmp;
    }
    buildCsr(n, m, raw, &GT);

    memset(visited, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1(i);
    }

    memset(visited, 0, sizeof(int) * n);
    for (int i = n - 1; i >= 0; i--) {
        if (!visited[post_order[i]]) {
            dfs2(post_order[i], current_scc++);
        }
    }

    for (int i = 0; i < m; i++) {
        int tmp = raw[i].u;
        raw[i].u = raw[i].v;
        raw[i].v = tmp;
    }

    Edge *cond = malloc(m * sizeof(Edge));
    int cond_m = 0;
    for (int i = 0; i < m; i++) {
        int from = scc[raw[i].u];
        int to = scc[raw[i].v];
        if (from != to) {
            cond[cond_m++] = (Edge){from, to};
        }
    }
    qsort(cond, cond_m, sizeof(Edge), compareEdges);

    int *inDeg = calloc(current_scc, sizeof(int));
    int *outDeg = calloc(current_scc, sizeof(int));
    int uniq_m = 0;
    for (int i = 0; i < cond_m; i++) {
        if (i == 0 || (cond[i].u != cond[i-1].u || cond[i].v != cond[i-1].v)) {
            outDeg[cond[i].u]++;
            inDeg[cond[i].v]++;
            cond[uniq_m++] = cond[i];
        }
    }

    printf("%d\n", current_scc);
    for (int i = 0; i < n; i++) printf("%d%c", scc[i], i == n - 1 ? '\n' : ' ');

    printf("%d\n", uniq_m);
    for (int i = 0; i < uniq_m; i++) {
        printf("%d %d\n", cond[i].u, cond[i].v);
    }

    int sources = 0, sinks = 0;
    for (int i = 0; i < current_scc; i++) {
        if (inDeg[i] == 0) sources++;
        if (outDeg[i] == 0) sinks++;
    }

    if (current_scc == 1) printf("0\n");
    else printf("%d\n", sources > sinks ? sources : sinks);

    free(raw);
    free(cond);
    free(inDeg);
    free(outDeg);
    return 0;
}