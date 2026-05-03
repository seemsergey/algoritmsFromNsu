//
// Created by SeemS on 29.11.2025.
//
//второй вариант(с листами)

#include <stdlib.h>
#include <string.h>

void h(char val);

typedef struct Node {
    char *val;
    struct Node *next;
} Node;
Node* hashTable[m];

int add(char *val, Node **hashTable) {
    int t = h(val);
    if (hashTable[t]) {
        hashTable[t]->val = (char *) malloc(strlen(val));
        strcpy(hashTable[t]->val, val);
    } else {
        Node* cur = hashTable[t];
        while (cur->next != NULL) {
            if (strcmp(cur->val, val) == 0) {
                return 1;
            }
            cur = cur->next;
        }
        if (strcmp(cur->val, val) == 0) {
            return 1;
        }
        c
    }

}