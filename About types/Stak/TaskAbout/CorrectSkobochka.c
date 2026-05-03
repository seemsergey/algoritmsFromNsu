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
    TUn Value;
    EType Type;
    TListImpl* Next;
} TListImpl;

typedef struct QueueWithPriority {
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


int Check(char *str, int size) {
    TStack* Stack = (TStack*)malloc(sizeof(TStack));
    char last;
    for (int i = 0; i < size; i++) {
        if (str[i] == '[' || str[i] == '(') {
            Push(Stack, str[i]);
        } else {
            Pop(stacl, &last);
            if (!((last == '(' && str[i] == ')') || (last == '[' && str[i] == ']'))) {
                printf("NO");
                return 0;
            }
        }
    }
}