//
// Created by SeemS on 11.03.2026.
//

#include <stdio.h>
#include <stdlib.h>

// Структура узла связного списка (для списка смежности)
typedef struct Node {
    int data;
    struct Node* next;
} Node;


// Структура графа
typedef struct Graph {
    int numVertices;
    Node** adjLists; // Массив списков смежности
    int* inDegree;   // Массив входящих степеней для алгоритма Кана
} Graph;

// Структура минимальной кучи (Priority Queue)
typedef struct MinHeap {
    int* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap* heap, int value) {
    heap->data[heap->size] = value;
    int i = heap->size++;
    // Heapify Up
    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int pop(MinHeap* heap) {
    if (heap->size <= 0) return -1;
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    // Heapify Down
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap->size && heap->data[left] < heap->data[smallest])
            smallest = left;
        if (right < heap->size && heap->data[right] < heap->data[smallest])
            smallest = right;

        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else break;
    }
    return root;
}



int topoSort() {

}

int main() {
    int in, out;
    while (scanf("%d%d", &in, &out) == 2) {

    }
}