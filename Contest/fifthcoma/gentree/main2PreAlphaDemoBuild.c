//
// Created by SeemS on 18.03.2026.
//

#include <stddef.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* first_child;
    struct TreeNode* next_sibling;
} TreeNode;

// Пример функции создания узла
TreeNode* create_node(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->first_child = NULL;
    node->next_sibling = NULL;
    return node;
}

