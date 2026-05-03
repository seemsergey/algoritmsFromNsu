//
// Created by SeemS on 11.03.2026.
//

// dfs(v)
//     colors[v] := 1
//     for p in { (v, p) | (v, p) ∈ E }:
//         if colors[p] == 1:
//             print "Not a DAG"
//             exit
//         if colors[p] == 0:
//             dfs(p)
//     colors[v] := 2
//     stack.push(v)
//
// colors[|V|] := {0};
// stack := {};
// for v in V:
//     if colors[v] != 2:
//         dfs(v)
// while !stack.empty():
//     print(stack.top())
//     stack.pop()

#include <stdio.h>
#include <stdlib.h>


enum Color {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2
};

// Структура узла списка смежности
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Структура графа
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* colors;
} Graph;

// Глобальные переменные для стека (согласно логике псевдокода)
int* stack;
int top = -1;

// Функция для добавления элемента в стек
void push(int v) {
    stack[++top] = v;
}

// Функция для создания узла
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Функция создания графа
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->colors = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->colors[i] = WHITE;
    }
    return graph;
}

// Добавление ориентированного ребра
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Рекурсивная функция DFS (основана на вашем псевдокоде)
void dfs(Graph* graph, int v) {
    // colors[v] := 1
    graph->colors[v] = GRAY;

    // for p in { (v, p) | (v, p) ∈ E }:
    Node* temp = graph->adjLists[v];
    while (temp != NULL) {
        int p = temp->vertex;

        // if colors[p] == 1: print "Not a DAG"; exit
        if (graph->colors[p] == GRAY) {
            printf("Not a DAG\n");
            exit(1); // Завершение программы при обнаружении цикла
        }

        // if colors[p] == 0: dfs(p)
        if (graph->colors[p] == WHITE) {
            dfs(graph, p);
        }
        temp = temp->next;
    }

    // colors[v] := 2
    graph->colors[v] = BLACK;
    // stack.push(v)
    push(v);
}

int main() {
    int n = 6; // Количество вершин
    Graph* graph = createGraph(n);
    stack = malloc(n * sizeof(int));

    // Пример графа (ориентированный ациклический граф)
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    // for v in V: if colors[v] != 2: dfs(v)
    for (int i = 0; i < n; i++) {
        if (graph->colors[i] != BLACK) {
            dfs(graph, i);
        }
    }

    // while !stack.empty(): print(stack.top()); stack.pop()
    printf("Topological Sort: ");
    while (top != -1) {
        printf("%d ", stack[top]);
        top--;
    }
    printf("\n");

    // Очистка памяти
    free(stack);
    for (int i = 0; i < n; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph->colors);
    free(graph);

    return 0;
}