#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct TEdge {
    int from;
    int to;
    int cost;
} TEdge;

// BFS для проверки достижимости всех вершин от корня R
int BFS(int n, int m, int root, TEdge* Edges) {
    int *offset = (int *)calloc(n + 1, sizeof(int));
    int *adj = (int *)malloc(m * sizeof(int));
    int *temp_count = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < m; i++) offset[Edges[i].from + 1]++;
    for (int i = 1; i <= n; i++) offset[i] += offset[i - 1];
    for (int i = 0; i < m; i++) {
        int from = Edges[i].from;
        adj[offset[from] + temp_count[from]] = Edges[i].to;
        temp_count[from]++;
    }

    int *visited = (int *)calloc(n, sizeof(int));
    int *queue = (int *)malloc(n * sizeof(int));
    int head = 0, tail = 0;

    queue[tail++] = root;
    visited[root] = 1;
    int visited_count = 1;

    while (head < tail) {
        int from = queue[head++];
        for (int i = offset[from]; i < offset[from + 1]; i++) {
            int to = adj[i];
            if (!visited[to]) {
                visited[to] = 1;
                visited_count++;
                queue[tail++] = to;
            }
        }
    }

    free(offset); free(adj); free(temp_count); free(visited); free(queue);
    return (visited_count == n);
}

int main() {
    int N, M, R;
    if (scanf("%d %d %d", &N, &M, &R) != 3) return 0;

    TEdge *Edges = malloc(M * sizeof(TEdge));
    int E = 0;
    for (int i = 0; i < M; i++) {
        int from, to, cost;
        scanf("%d %d %d", &from, &to, &cost);
        if (to != R && from != to) { // Игнорируем входящие в корень и петли
            Edges[E].from = from;
            Edges[E].to = to;
            Edges[E].cost = cost;
            E++;
        }
    }
    //Смотрим достижимость вершин от корня
    if (!BFS(N, E, R, Edges)) {
        printf("IMPOSSIBLE\n");
        free(Edges);
        return 0;
    }

    long long res = 0;
    int V = N;
    int root = R;

    while (1) {
        long long minCost[V];
        int parent[V];
        // Инициализируем
        for (int i = 0; i < V; i++) {
            minCost[i] = LLONG_MAX;
            parent[i] = -1;
        }

        // 1. Находим минимальное входящее ребро для каждой вершины
        for (int i = 0; i < E; i++) {
            if (Edges[i].from != Edges[i].to && Edges[i].cost < minCost[Edges[i].to]) {
                minCost[Edges[i].to] = Edges[i].cost;
                parent[Edges[i].to] = Edges[i].from;
            }
        }

        // 2. Считаем предварительную стоимость
        for (int i = 0; i < V; i++) {
            if (i == root) continue;
            res += minCost[i];
        }

        // 3. Поиск циклов
        int cycleId[V];
        int visited[V];
        for (int i = 0; i < V; i++) {
            cycleId[i] = -1;
            visited[i] = -1;
        }

        int numCycle = 0;
        for (int i = 0; i < V; i++) {
            if (i == root) continue;
            int curr = i;
            // Идем вверх по родителям пока не найдем корень или цикл
            while (curr != root && visited[curr] == -1 && cycleId[curr] == -1) {
                visited[curr] = i;
                curr = parent[curr];
            }

            // Если нашли узел, помеченный этим же проходом i - это цикл
            if (curr != root && cycleId[curr] == -1 && visited[curr] == i) {
                int start = curr;
                do {
                    cycleId[curr] = numCycle;
                    curr = parent[curr];
                } while (curr != start);
                numCycle++;
            }
        }
        //Если циклов нет, то все замечательно)
        if (numCycle == 0) {
            break;
        }

        // Добавляем ID для вершин, не вошедших в циклы
        for (int i = 0; i < V; i++) {
            if (cycleId[i] == -1) cycleId[i] = numCycle++;
        }

        // 4. Стягивание графа
        for (int i = 0; i < E; i++) {
            int old_v = Edges[i].to;
            Edges[i].from = cycleId[Edges[i].from];
            Edges[i].to = cycleId[Edges[i].to];
            if (Edges[i].from != Edges[i].to) {
                Edges[i].cost -= minCost[old_v]; // Пересчет веса
            }
        }

        root = cycleId[root];
        V = numCycle;
    }

    printf("%lld\n", res);
    free(Edges);
    return 0;
}