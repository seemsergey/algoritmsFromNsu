//
// Created by SeemS on 28.04.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAX_NODES 400005

int parent[MAX_NODES];
int rank[MAX_NODES];

int dsu_parent[MAX_NODES];
int krt_children[MAX_NODES][2]; // [node][0] = left, [node][1] = right
int node_weight[MAX_NODES];
int visited[MAX_NODES];
int lcaClass[MAX_NODES];        // Хранит текущего предка

long long answers[MAXN];        // Ответы для запросов

void makeSet(const int N) {
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Поиск для Крускала
int findSet(const int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v]);
}

// Поиск для Тарьяна
int findSetTarjan(const int v) {
    if (v == dsu_parent[v])
        return v;
    return dsu_parent[v] = findSetTarjan(dsu_parent[v]);
}

// Объединение для Тарьяна (строго child подчиняется par)
void unionTarjan(int child, int par) {
    int a = findSetTarjan(child);
    int b = findSetTarjan(par);
    if (a != b) {
        dsu_parent[a] = b;
    }
}

typedef struct TEdge {
    int from, to, weight;
} TEdge;

int compareEdges(const void *a, const void *b) {
    const TEdge *edgeA = (TEdge *) a;
    const TEdge *edgeB = (TEdge *) b;

    if (edgeA->weight < edgeB->weight) return -1;
    if (edgeA->weight > edgeB->weight) return 1;
    return 0;
}

typedef struct {
    int u, v, cost, id;
} TQuery;

TQuery queries[MAXN * 2]; // 2*Q запросов (в обе стороны)
int q_start[MAX_NODES];   // Индекс начала запросов для вершины u

int compareQueries(const void *a, const void *b) {
    return ((TQuery *)a)->u - ((TQuery *)b)->u;
}

// Тарьян
void Tarjan(int vertex, int N) {
    visited[vertex] = 1;
    lcaClass[vertex] = vertex;

    if (krt_children[vertex][0] != -1) {
        int children[2] = {krt_children[vertex][0], krt_children[vertex][1]};
        for (int i = 0; i < 2; i++) {
            int v = children[i];
            Tarjan(v, N);
            unionTarjan(v, vertex);
            lcaClass[findSetTarjan(v)] = vertex;
        }
    }

    if (vertex < N) {
        int start = q_start[vertex];
        int end = q_start[vertex + 1]; // Теперь это безопасно
        for (int i = start; i < end; i++) {
            int v = queries[i].v;
            if (visited[v]) {
                int lca = lcaClass[findSetTarjan(v)];
                int max_edge_w = node_weight[lca];
                long long diff = (long long)max_edge_w - queries[i].cost;
                answers[queries[i].id] = (diff > 0) ? diff : 0;
            }
        }
    }
}

TEdge edges[MAXN];

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    for (int i = 0; i < N - 1; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }
    qsort(edges, N - 1, sizeof(TEdge), compareEdges);

    makeSet(MAX_NODES);

    for (int i = 0; i < MAX_NODES; i++) {
        krt_children[i][0] = -1;
        krt_children[i][1] = -1;
    }

    int node_count = N;
    for (int i = 0; i < N - 1; i++) {
        int from = findSet(edges[i].from);
        int to = findSet(edges[i].to);

        if (from != to) {
            int v = node_count++;
            node_weight[v] = edges[i].weight;

            krt_children[v][0] = from;
            krt_children[v][1] = to;

            // В KRT новый узел обязан стать корнем
            parent[from] = v;
            parent[to] = v;
            parent[v] = v;
        }
    }

    // Чтение запросов
    int Q;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        queries[i * 2] = (TQuery){a, b, c, i};
        queries[i * 2 + 1] = (TQuery){b, a, c, i};
    }

    // Сортируем массив запросов по первому серверу
    qsort(queries, Q * 2, sizeof(TQuery), compareQueries);

    int current_q = 0;
    for (int i = 0; i <= node_count; i++) {
        // Пропускаем в массиве queries все, что относится к вершинам меньше i
        while (current_q < Q * 2 && queries[current_q].u < i) {
            current_q++;
        }
        q_start[i] = current_q;
    }

    memset(visited, 0, sizeof(visited));
    memset(lcaClass, 0, sizeof(lcaClass));
    for (int i = 0; i < node_count; i++) {
        dsu_parent[i] = i;
    }

    Tarjan(node_count - 1, N);

    for (int i = 0; i < Q; i++) {
        printf("%lld%c", answers[i], (i == Q - 1 ? '\n' : ' '));
    }

    return 0;
}