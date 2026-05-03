#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXM 500005
#define INF 1000000000000000000LL

typedef struct {
    int u, v, weight;
} RawEdge;

int offset[MAXN + 1];
int adj[MAXM];
int weights[MAXM];
long long dists[10][MAXN];

int compareEdges(const void *a, const void *b) {
    RawEdge *e1 = (RawEdge *)a;
    RawEdge *e2 = (RawEdge *)b;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

typedef struct {
    int node;
    long long d;
} HeapNode;

HeapNode heap[MAXM + MAXN]; 
int heapSize = 0;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void sift_up(int v) {
    while (v > 1 && heap[v].d < heap[v / 2].d) {
        swap(&heap[v], &heap[v / 2]);
        v /= 2;
    }
}

void sift_down(int v) {
    while (2 * v <= heapSize) {
        int l = 2 * v;
        int r = 2 * v + 1;
        int u = (r <= heapSize && heap[r].d < heap[l].d) ? r : l;
        if (heap[v].d <= heap[u].d) break;
        swap(&heap[v], &heap[u]);
        v = u;
    }
}

void push(int node, long long d) {
    heap[++heapSize].node = node;
    heap[heapSize].d = d;
    sift_up(heapSize);
}

HeapNode pop() {
    HeapNode res = heap[1];
    heap[1] = heap[heapSize--];
    sift_down(1);
    return res;
}

void dijkstra(int N, int startPoint, long long *dist) {
    heapSize = 0; // ОБЯЗАТЕЛЬНО обнуляем
    for (int i = 0; i < N; i++) dist[i] = INF;
    
    dist[startPoint] = 0;
    push(startPoint, 0);

    while (heapSize > 0) {
        HeapNode current = pop();
        int u = current.node;
        if (current.d > dist[u]) continue;

        for (int j = offset[u]; j < offset[u + 1]; j++) {
            int v = adj[j];
            if (dist[u] + weights[j] < dist[v]) {
                dist[v] = dist[u] + weights[j];
                push(v, dist[v]);
            }
        }
    }
}

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    RawEdge *Edges = malloc(sizeof(RawEdge) * M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &Edges[i].u, &Edges[i].v, &Edges[i].weight);
    }

    // Строим CSR
    qsort(Edges, M, sizeof(RawEdge), compareEdges);
    int current_edge = 0;
    for (int i = 0; i < N; i++) {
        offset[i] = current_edge;
        while (current_edge < M && Edges[current_edge].u == i) {
            adj[current_edge] = Edges[current_edge].v;
            weights[current_edge] = Edges[current_edge].weight;
            current_edge++;
        }
    }
    offset[N] = M;

    free(Edges); // ОСВОБОЖДАЕМ ПАМЯТЬ (6 Мб), чтобы влезть в 32 Мб

    int K;
    scanf("%d", &K);
    int startPoints[10];
    for (int i = 0; i < K; i++) scanf("%d", &startPoints[i]);

    for (int i = 0; i < K; i++) {
        dijkstra(N, startPoints[i], dists[i]);
    }

    long long min_max_dist = INF;
    int best_node = -1;

    for (int i = 0; i < N; i++) {
        long long current_max = 0;
        int possible = 1;
        for (int j = 0; j < K; j++) {
            if (dists[j][i] == INF) {
                possible = 0;
                break;
            }
            if (dists[j][i] > current_max) current_max = dists[j][i];
        }

        if (possible) {
            if (current_max < min_max_dist) {
                min_max_dist = current_max;
                best_node = i;
            }
        }
    }

    if (best_node == -1) printf("-1\n");
    else printf("%d\n%lld\n", best_node, min_max_dist);

    return 0;
}