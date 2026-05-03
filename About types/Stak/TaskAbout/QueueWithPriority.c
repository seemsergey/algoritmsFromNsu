//
// Created by SeemS on 18.10.2025.
//

#include <stdlib.h>

typedef enum EType {
    INT,
    DOUBLE,
} EType;

typedef union {
    int ValueInt;;
    double ValueDouble;
} TUn;

typedef struct TListImpl{
    int Id;
    int Priority;
    TListImpl* Next;
} TListImpl;

typedef struct QueueWithPriority {
    TListImpl* Begin;
    TListImpl* Tail;
} QueueWithPriority;

int Push(QueueWithPriority* queue, int id, int priority) {
    if (!queue)
        return 1;
    TListImpl* cur = queue->Begin;
    last = queue->Begin;
    while (cur && cur->Next) {
        if (cur->Priority < priority) {
            break;
        }
        else {
            last = cur;
            cur = cur->Next;
        }
    }
    TListImpl* newNode = (TListImpl*)malloc(sizeof(TListImpl));
    newNode->Id = id;
    newNode->Priority = priority;
    if (!cur) {
        queue->Begin = newNode;
        queue->Begin->Next = NULL;
        queue->Tail = queue->Begin;
        return 0;
    } else if (!last) {
        TListImpl prevHead = queue->Begin;
        queue->Begin = newNode;
        queue->Begin->Next = NULL;
        return 0;
    } else if (cur->Priority < priority) {
        cur->Next = newNode;
        cur->Next->Next = NULL;
        queue->Tail = cur->Next;
        return 0;
    } else {
        last->next = newNode;
        last->next->Next = cur;
        return 0;
    }
    return 1;
}