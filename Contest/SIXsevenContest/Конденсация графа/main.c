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
int post_order[MAXN], post_ptr = 0;

int scc[MAXN], current_scc = 0;

int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *) a;
    Edge *e2 = (Edge *) b;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

void buildCsr(int n, int m, Edge *raw, CSRGraph *graph) {
    qsort(raw, m, sizeof(Edge), compareEdges);

    int ptr = 0;
    for (int i = 0; i < n; i++) {
        graph->offset[i] = ptr;
        while (ptr < m && raw[ptr].u == i) {
            graph->edges[ptr] = raw[ptr].v;
            ptr++;
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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Edge *raw = malloc(sizeof(Edge) * m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &raw[i].u, &raw[i].v);
    }

    // строим граф
    buildCsr(n, m, raw, &G);

    // транспонируем
    for (int i = 0; i < m; i++) {
        int t = raw[i].u;
        raw[i].u = raw[i].v;
        raw[i].v = t;
    }
    buildCsr(n, m, raw, &GT);

    // dfs1
    memset(visited, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1(i);
    }

    // dfs2
    memset(visited, 0, sizeof(int) * n);
    for (int i = n - 1; i >= 0; i--) {
        int v = post_order[i];
        if (!visited[v]) {
            dfs2(v, current_scc++);
        }
    }

    for (int i = 0; i < m; i++) {
        int t = raw[i].u;
        raw[i].u = raw[i].v;
        raw[i].v = t;
    }

    Edge *cond = malloc(sizeof(Edge) * m);
    int cond_m = 0;

    for (int i = 0; i < m; i++) {
        int a = scc[raw[i].u];
        int b = scc[raw[i].v];
        if (a != b) {
            cond[cond_m++] = (Edge){a, b};
        }
    }

    qsort(cond, cond_m, sizeof(Edge), compareEdges);

    int *inDeg = calloc(current_scc, sizeof(int));
    int *outDeg = calloc(current_scc, sizeof(int));

    int uniq_m = 0;
    for (int i = 0; i < cond_m; i++) {
        if (i == 0 || cond[i].u != cond[i - 1].u || cond[i].v != cond[i - 1].v) {
            cond[uniq_m++] = cond[i];
            outDeg[cond[i].u]++;
            inDeg[cond[i].v]++;
        }
    }


    int *head = malloc(sizeof(int) * current_scc);
    int *to = malloc(sizeof(int) * uniq_m);
    int *next = malloc(sizeof(int) * uniq_m);

    for (int i = 0; i < current_scc; i++) head[i] = -1;

    for (int i = 0; i < uniq_m; i++) {
        to[i] = cond[i].v;
        next[i] = head[cond[i].u];
        head[cond[i].u] = i;
    }

    int *queue = malloc(sizeof(int) * current_scc);
    int ql = 0, qr = 0;

    int *inDeg_copy = malloc(sizeof(int) * current_scc);
    memcpy(inDeg_copy, inDeg, sizeof(int) * current_scc);

    for (int i = 0; i < current_scc; i++) {
        if (inDeg_copy[i] == 0) queue[qr++] = i;
    }

    int *new_id = malloc(sizeof(int) * current_scc);
    int id = 0;

    while (ql < qr) {
        int u = queue[ql++];
        new_id[u] = id++;

        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            if (--inDeg_copy[v] == 0)
                queue[qr++] = v;
        }
    }

    for (int i = 0; i < n; i++)
        scc[i] = new_id[scc[i]];

    for (int i = 0; i < uniq_m; i++) {
        cond[i].u = new_id[cond[i].u];
        cond[i].v = new_id[cond[i].v];
    }

    qsort(cond, uniq_m, sizeof(Edge), compareEdges);


    printf("%d\n", current_scc);

    for (int i = 0; i < n; i++) {
        printf("%d%c", scc[i], i == n - 1 ? '\n' : ' ');
    }

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

    return 0;
}
