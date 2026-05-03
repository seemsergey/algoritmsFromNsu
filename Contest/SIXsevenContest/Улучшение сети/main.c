//
// Created by SeemS on 28.04.2026.
//


/*
* bool visited[n]

function union(x : int, y : int, newAncestor : int):
    leader = dsuUnion(x, y)         // объединяем классы вершин x и y и получаем нового представителя класса
    lcaClass[leader] = newAncestor  // устанавливаем нового предка представителю множества

// можно запустить от любой вершины дерева в самый первый раз
function dfs(v : int):
    visited[v] = true
    lcaClass[v] = v
    foreach u : (v, u) in G
        if not visited[u]
            dfs(u)
            union(v, u, v)
    for (u : ⟨v,u⟩ — есть такой запрос)
        if visited[u]
            запомнить, что ответ для запроса ⟨v,u⟩ = lcaClass[find[u]]
 */

#define MAXN 200005
#include <stdio.h>
#include <stdlib.h>

int parent[MAXN];
int rank[MAXN];

void makeSet(const int N) {
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}
// Поиск с оптимизацией (сжатие путей)
int findSet(const int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v]);
}

// Объединение по рангу
void unionSets(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (rank[a] < rank[b]) {
            parent[a] = b;
        } else if (rank[a] > rank[b]) {
            parent[b] = a;
        } else {
            parent[a] = b;
            rank[b]++;
        }
    }
}

typedef struct TEdge {
    int from, to, weight, id;
} TEdge;

int compareEdges(const void *a, const void *b) {
    const TEdge *edgeA = (TEdge *) a;
    const TEdge *edgeB = (TEdge *) b;

    if (edgeA->weight < edgeB->weight) return -1;
    if (edgeA->weight > edgeB->weight) return 1;
    return 0;
}


int main(void) {
    int N;
    scanf("%d",&N);
    TEdge edges[N-1];
    for (int i = 0; i < N-1; i++) {
        scanf("%d %d %d",&edges[i].from,&edges[i].to, &edges[i].weight);
    }
    qsort(edges,N,sizeof(TEdge),compareEdges);

    makeSet(N);

    //Kruskal Reconstruction Tree

}