#ifndef CSR_H
#define CSR_H

#include <stdio.h>
#include <stdlib.h>

// Входная структура для ребра
typedef struct {
    int u;      // Откуда
    int v;      // Куда
    int weight; // Вес (опционально)
} RawEdge;

// Структура CSR графа
typedef struct {
    int num_vertices;
    int num_edges;
    int *offset;  // Массив смещений (размер V + 1), он же C в вашем коде
    int *adj;     // Массив смежных вершин (размер E), он же R
    int *weights; // Массив весов (размер E)
} CSRGraph;

// Функция для построения CSR из списка ребер
// num_vertices: количество вершин
// num_edges: количество ребер
// edges: массив ребер (будет отсортирован внутри функции)
CSRGraph* build_csr(int num_vertices, int num_edges, RawEdge *edges);

// Освобождение памяти
void free_csr(CSRGraph *graph);

// Вспомогательная функция для печати (отладка)
void print_csr_info(const CSRGraph *graph);

#endif