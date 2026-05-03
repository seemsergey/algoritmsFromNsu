//TREES

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
    struct TListImpl* Next;
} TListImpl;

typedef struct TQeue {
    TListImpl* Head;
    TListImpl* Tail;
} TQeue;

// Инициализация очереди
void InitQueue(TQeue* Queue) {
    Queue->Head = NULL;
    Queue->Tail = NULL;
}

// Проверка на пустоту
int IsEmpty(TQeue* Queue) {
    return Queue->Head == NULL;
}

// Добавить элемент в очередь (в конец)
int Push(TQeue* Queue, int Value) {
    TListImpl* node = malloc(sizeof(TListImpl));
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
int Pop(TQeue* Queue) {
    if (IsEmpty(Queue)) return 0;

    TListImpl* temp = Queue->Head;
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