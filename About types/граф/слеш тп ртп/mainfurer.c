//
// Created by SeemS on 15.04.2026.
//
//все рёбра с весом 0 имеют тп
#define N 6
#define M 10


void push(TPriorQueue *pq, int  v, int d);

int main() {
    int offset[N];
    int edges[M];
    int weight[M];
    int d[N];
    int usedTP[N];

    TPriorQueue pq;
    push(&pq, 0, 0);
    while (!Empty(&pq)) {
        int d, v;
        pop(&pq, &d, &v);
        for (int j = offset[N]; j < offset[N+1]; j++) {
            if (weight[j] == 0 && usedTP[v]) {
                continue;
            }
            int u = edges[j];
            if (d[u] > d[v] + weight[j]) {
                d[u] = d[v] + weight[j];
                if (weight[j] == 0) {
                    usedTP[v] = 1;
                }
            }
        }
    }
}