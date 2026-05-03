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

typedef struct TQeue {
    TListImpl* Head;
    TListImpl* Tail;
} TQeue;

int Push(TQeue* Queue, int Value) {
    //аналогичшно StackOnList
}

int Pop(TQeue* Queue) {
    //аналогично
}