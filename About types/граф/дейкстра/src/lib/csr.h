#ifndef CSR_H
#define CSR_H

#include <stdio.h>
#include <stdlib.h>

// Входная структура для ребра
typedef struct {
    int from; // Откуда
    int to; // Куда
    long long weight; // Вес
} TEdge;

// Структура CSR графа
typedef struct {
    int num_vertices;
    int num_edges;
    int *offset; // Массив смещений
    int *adj; // Массив смежных вершин
    long long *weights; // Массив весов
} TCSRGraph;

// Функция для построения CSR из списка ребер
// num_vertices: количество вершин
// num_edges: количество ребер
// edges: массив ребер (будет отсортирован внутри функции)
TCSRGraph *BuildCSR(int numVertices, int numEdges, TEdge *edges);

// Освобождение памяти
void FreeCSR(TCSRGraph *graph);

#endif