#include <stdio.h>
#include <stdlib.h>

enum Color {
    RED = 0,
    BLACK = 1
};

typedef struct TNode {
    int value;
    struct TNode *parent;
    struct TNode *left;
    struct TNode *right;
    enum Color color;
} TNode;

int getBlackHeight(TNode* node) {
    int blackHeight = 0;
    TNode* current = node;

    while (current != NULL) {
        if (current->color == BLACK) {
            blackHeight++;
        }
        current = current->left;
    }

    // Прибавляем 1, так как NULL-листья (NIL) тоже считаются черными
    return blackHeight + 1;
}

TNode* createNode(int value) {
    TNode* node = (TNode*)malloc(sizeof(TNode));
    node->value = value;
    node->left = node->right = node->parent = NULL;
    node->color = RED; // Новые узлы всегда красные
    return node;
}


void rotateLeft(TNode **treeRoot, TNode *pivot) {
    TNode *rightChild = pivot->right;

    // 1. Перебрасываем левое поддерево правого ребенка к pivot
    pivot->right = rightChild->left;
    if (rightChild->left != NULL) {
        rightChild->left->parent = pivot;
    }

    // 2. Устанавливаем родителя для нового "верхнего" узла (rightChild)
    rightChild->parent = pivot->parent;

    if (pivot->parent == NULL) {
        *treeRoot = rightChild; // pivot был корнем
    } else if (pivot == pivot->parent->left) {
        pivot->parent->left = rightChild;
    } else {
        pivot->parent->right = rightChild;
    }

    // 3. Завершаем поворот
    rightChild->left = pivot;
    pivot->parent = rightChild;
}

void rotateRight(TNode **treeRoot, TNode *pivot) {
    TNode *leftChild = pivot->left;

    // 1. Перебрасываем правое поддерево левого ребенка к pivot
    pivot->left = leftChild->right;
    if (leftChild->right != NULL) {
        leftChild->right->parent = pivot;
    }

    // 2. Устанавливаем родителя для левого ребенка
    leftChild->parent = pivot->parent;

    if (pivot->parent == NULL) {
        *treeRoot = leftChild;
    } else if (pivot == pivot->parent->right) {
        pivot->parent->right = leftChild;
    } else {
        pivot->parent->left = leftChild;
    }

    // 3. Завершаем поворот
    leftChild->right = pivot;
    pivot->parent = leftChild;
}

void balanceAfterInsert(TNode **treeRoot, TNode *newNode) {
    // Пока нарушено свойство (красный узел под красным)
    while (newNode->parent != NULL && newNode->parent->color == RED) {
        TNode *parent = newNode->parent;
        TNode *grandparent = parent->parent;

        // Если родитель — левый ребенок деда
        if (parent == grandparent->left) {
            TNode *uncle = grandparent->right;

            // Случай 1: Дядя тоже красный — просто перекрашиваем
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                newNode = grandparent; // Проверяем деда на новом цикле
            }
            else {
                // Случай 2: Дядя черный, а новый узел "внутренний" (справа)
                if (newNode == parent->right) {
                    newNode = parent;
                    rotateLeft(treeRoot, newNode);
                    parent = newNode->parent; // Обновляем после поворота
                }
                // Случай 3: Дядя черный, а новый узел "внешний" (слева)
                parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(treeRoot, grandparent);
            }
        }
        // Зеркальный случай: родитель — правый ребенок деда
        else {
            TNode *uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                newNode = grandparent;
            } else {
                if (newNode == parent->left) {
                    newNode = parent;
                    rotateRight(treeRoot, newNode);
                    parent = newNode->parent;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(treeRoot, grandparent);
            }
        }
    }
    // Корень всегда должен быть черным
    (*treeRoot)->color = BLACK;
}

void insert(TNode **treeRoot, int value) {
    TNode *newNode = createNode(value);
    TNode *current = *treeRoot;
    TNode *potentialParent = NULL;

    // Спускаемся вниз как в обычном бинарном дереве
    while (current != NULL) {
        potentialParent = current;
        if (newNode->value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = potentialParent;

    if (potentialParent == NULL) {
        *treeRoot = newNode; // Дерево было пустым
    } else if (newNode->value < potentialParent->value) {
        potentialParent->left = newNode;
    } else {
        potentialParent->right = newNode;
    }

    balanceAfterInsert(treeRoot, newNode);
}

int main(void) {
    int n;
    if (scanf("%d", &n) !=1 ) {
        return 0;
    }
    if (n == 0) {
        printf("0");
        return 0;
    }
    TNode *root = NULL;
    for (int i = 0; i < n; i++) {
        int value;
        if (scanf("%d", &value)) {
            insert(&root, value);
        }
    }
    printf("%d", getBlackHeight(root));
}