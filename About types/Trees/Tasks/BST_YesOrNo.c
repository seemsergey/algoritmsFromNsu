// Дано: бинарное дерево поиска обход в шиирину
//      N
// 5 7 9 1 11 6
// Вывод: yes/no - является ли BST?

#include <stdio.h>
#include <stdlib.h>

//Дерево
typedef struct ThreeNode {
    struct ThreeNode *Left;
    struct ThreeNode *Right;
    int value;
} ThreeNode;

// === Перечисления ===
typedef enum EWalkInVoid {
    Pre,
    In,
    Post
} EWalkInVoid;

typedef enum EType {
    INT,
    DOUBLE,
} EType;

// === Очередь ===
typedef union {
    int ValueInt;
    double ValueDouble;
} TUn;

typedef struct TListImpl {
    TUn Value;
    EType Type;
    struct TListImpl *Next;
} TListImpl;

typedef struct TQeue {
    TListImpl *Head;
    TListImpl *Tail;
} TQeue;

// Инициализация очереди
void InitQueue(TQeue *Queue) {
    Queue->Head = NULL;
    Queue->Tail = NULL;
}

// Проверка на пустоту
int IsEmpty(TQeue *Queue) {
    return Queue->Head == NULL;
}

// Добавить элемент в очередь (в конец)
int Push(TQeue *Queue, int Value) {
    TListImpl *node = malloc(sizeof(TListImpl));
    if (!node) return 0;

    node->Value.ValueInt = Value;
    node->Type = INT;
    node->Next = NULL;

    if (Queue->Tail) {
        Queue->Tail->Next = node;
    } else {
        Queue->Head = node;
    }
    Queue->Tail = node;
    return 1;
}

// Удалить элемент из очереди (с начала)
int Pop(TQeue *Queue) {
    if (IsEmpty(Queue)) return 0;

    TListImpl *temp = Queue->Head;
    int value = temp->Value.ValueInt;

    Queue->Head = temp->Next;
    if (!Queue->Head)
        Queue->Tail = NULL;

    free(temp);
    return value;
}

int WalkInWidth(ThreeNode *root, ThreeNode *node) {
    TQeue Queue;
    if (!root) {
        return 1;
    }
    Push(&Queue, *root);

    while (!IsEmpety) {
        ThreeNode *buf = Pop(&Queue);
        Push(&Queue, root->Left);
        Push(&Queue, root->Right);
    }
}


ThreeNode *GeneratedBST(int *nums, int numsSize) { //востановить дерево из строки чисел по правилу бинарного поиска (2 * i + 1,  2 * i + 2)
    // ThreeNode *root = malloc(sizeof(ThreeNode*) * numsSize);
    // for (int i = 0; i < numsSize; i++) {
    //     ro
    // }
}

int isBST(ThreeNode *root, int type) {
    int  maxVal = root->value;
    int  minVal = root->value;

    if (root ->Left) {
        int t = isBST(root->Left, 0);
        if (t == -1) return -1;
        if (t > maxVal) return -1;
        minVal = t;
    }
    if (root ->Right) {
        int t = isBST(root->Right, 1);
        if (t == -1) return -1;
        if (t < root->value) return -1;
        maxVal = t;
    }
    if (type == 0) {
        return maxVal;
    } else {
        return minVal;
    }

}