#include <stdlib.h>
//
// Created by SeemS on 18.10.2025.
//
typedef enum EType {
    INT,
    DOUBLE,
} EType;

typedef union {
    int ValueInt;;
    double ValueDouble;
} TUn;

typedef struct TListImpl{
    TUn Value;
    EType Type;
    TListImpl* Next;
} TListImpl;

typedef struct Stack {
    TListImpl* Begin;
} TStack;

int Push(TStack* Stack, int Value) {
    if (!Stack) {
        return 1;
    }
    TListImpl* New = (TListImpl*)malloc(sizeof(TListImpl));
    New -> Value = Value;
    New -> Next = NULL;
    if (Stack->Begin == NULL) {
        Stack->Begin = New;
    } else {
        New -> Next = Stack->Begin;
        Stack->Begin = New;
    }
    return 0;
}


int F(int n) {
    TStack* Stack = (TStack*)malloc(sizeof(TStack));
    Push(Stack, 0);
    Push(Stack, 1);

}