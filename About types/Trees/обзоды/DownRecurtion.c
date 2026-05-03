//
// Created by SeemS on 25.10.2025.
////TREES

#include <stdio.h>
#include <stdlib.h>
//Дерево
typedef struct ThreeNode {
    struct ThreeNode *Left;
    struct ThreeNode *Right;
    int value;
} ThreeNode;
//Походы по дереву
typedef enum EWalkInVoid {
    Pre,
    In,
    Post
};

int WalkInVoid(ThreeNode *root, enum EWalkInVoid type) {
    if (!root) {
        return 1;
    }
    if (type == Pre) {
        printf("Pre\n", root->value);
        return WalkInVoid(root->Left, type);
    }
    if (root->Left) {
        return WalkInVoid(root->Left, type);
    }
    if (type == In) {
        printf("In\n", root->value);
    }
    if (root->Right) {
        return WalkInVoid(root->Right, type);
    }
    if (type == Post) {
        printf("In\n", root->value);
    }
}