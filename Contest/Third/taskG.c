#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10

typedef struct Node {
    char type; // 't', 'f', '!', '&', '|'
    struct Node* children[MAX_CHILDREN];
    int childCount;
} Node;

// Создание нового узла
Node* createNode(char type) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->childCount = 0;
    for (int i = 0; i < MAX_CHILDREN; i++)
        node->children[i] = NULL;
    return node;
}

// Добавление ребенка
void addChild(Node* parent, Node* child) {
    if (parent->childCount < MAX_CHILDREN) {
        parent->children[parent->childCount++] = child;
    }
}


// Освобождение памяти
void freeTree(Node* node) {
    for (int i = 0; i < node->childCount; i++)
        freeTree(node->children[i]);
    free(node);
}

Node* ExpressionToTree(char *s, int *pos){
    char c = s[*pos];

    if(c == 't' || c == 'f'){
        Node *node = createNode(c);
        (*pos)++;
        return node;
    } else if(c == '&' || c == '|'){
        Node* node = createNode(c);
        (*pos)+=2;
        while (s[(*pos)] != ')' ){
            node->children[node->childCount++] = ExpressionToTree(s, pos);
        }

        return node
    } else if ()

    return NULL;
}


int main() {
    char s[10001];
    scanf("%10000s", s);

    int pos = 0;
    Node* root = ExpressionToTree(s, &pos);

    char result = eval(root);
    printf("%c\n", result);

    freeTree(root);
    return 0;
}
