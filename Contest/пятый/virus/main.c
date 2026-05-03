#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 1000005

int dist[MAXN];
int queue[MAXN];
int head = 0, tail = 0;

// Очередь
void push(int data) {
    queue[tail++] = data;
}

int pop(void) {
    return queue[head++];
}

bool isEmpty() {
    return head == tail;
}

int edgeTo[MAXM]; 
int edgeNext[MAXM]; 
int edgeINF[MAXN];
int edgeCount = 0; 

void addEdge(int v, int u) {
    // v -> u
    edgeTo[edgeCount] = u;
    edgeNext[edgeCount] = edgeINF[v];
    edgeINF[v] = edgeCount++;

    // u -> v
    edgeTo[edgeCount] = v;
    edgeNext[edgeCount] = edgeINF[u];
    edgeINF[u] = edgeCount++;
}

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    for (int i = 0; i < N; i++) {
        edgeINF[i] = -1;
        dist[i] = -1;
    }

    for (int i = 0; i < M; i++) {
        int v, u;
        scanf("%d %d", &v, &u);
        addEdge(v, u);
    }

    int K;
    scanf("%d", &K);

    for (int i = 0; i < K; i++) {
        int startNode;
        scanf("%d", &startNode);
        dist[startNode] = 0;
        push(startNode);
    }

    while (!isEmpty()) {
        int curr = pop();

        for (int i = edgeINF[curr]; i != -1; i = edgeNext[i]) {
            int neighbor = edgeTo[i];
            if (dist[neighbor] == -1) { // Если еще не заражен
                dist[neighbor] = dist[curr] + 1;
                push(neighbor);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d%c", dist[i], (i == N - 1 ? '\n' : ' '));
    }

    return 0;
}