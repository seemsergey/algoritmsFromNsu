//
// Created by SeemS on 25.10.2025.
//

#include <stdlib.h>
#include <string.h>

int generateSummTree(int* arr, int n) {
    int* tree = (int *)malloc(sizeof(int) * n);
    memcpy(tree, arr, sizeof(int) * n);
    for (int i = n-1; i >= 0; i--) {
        tree[i] = tree[2*i + 1] + tree[2*i + 2];
    }
}
