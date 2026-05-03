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

struct TQueue {
    TStack InStack;
    TStack OutStack;
} TQueue;