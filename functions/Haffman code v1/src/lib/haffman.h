//
// Created by SeemS on 15.02.2026.
//

#ifndef LAB5_HAFFMAN_H
#define LAB5_HAFFMAN_H
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char ch;      // символ
    char code[256];        // строка вида "0101010"
} HuffmanCode;

typedef struct TreeNode {
    unsigned char ch; // символ
    size_t freq; // частота
    struct TreeNode *left; // левый потомок
    struct TreeNode *right; // правый потомок
    size_t height; // высота поддерева (для однозначности декода)
} TreeNode;

// Функции работы с деревом
TreeNode *createNode(unsigned char symbol, size_t freq, TreeNode *left, TreeNode *right, size_t height);
void clearTree(TreeNode *root);

// Функции работы с кучей
void heapInsert(TreeNode **heap, size_t *heapSize, TreeNode *node);
TreeNode *minSearch(TreeNode **heap, size_t *heapSize);

// Построение дерева и кодовой таблицы
void buildCodeTree(TreeNode **heap, size_t *heapSize);

TreeNode *createHuffmanTree(TreeNode **heap, size_t *heapSize);

void generateCodes(const TreeNode *root, HuffmanCode *codes, char *curCode, int lenCode);

#endif //LAB5_HAFFMAN_H