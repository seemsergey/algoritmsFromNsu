//Списки
// [] -> [] -> []
//не предполагает, что элементы лежат подряд


//РЕАЛИЗАЦИЯ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdlib.h>

typedef enum EType {
    INT,
    DOUBLE,
} EType;

typedef union {
    int ValueInt;;
    double ValueDouble;
} TUn;


typedef struct TListImpl {
    TListImpl *Next;
    TUn Value;
    EType Type;
} TListImpl;

typedef struct TList {
    TListImpl *Begin;
} TList;


int main() {
    TList list;
    list.Begin = NULL;
    Push(TUn value, EType type, TListImpl * list);
    Remove(int index, TList * list);
    Pop(TList * list);
    Add(int index, TUn value, EType type, TList * list);
}

TListImpl *AllocList(TUn value, EType type, TList *list) {
    TListImpl *el = (TListImpl *) malloc(sizeof(TListImpl));
    el->Value = value;
    el->Type = type;
    el->Next = NULL;
    return el;
}


int Push(TUn value, EType type, TList *list) {
    if (!list->Begin) {
        list->Begin = (TListImpl *) malloc(sizeof(TListImpl));
        list->Begin = AllocList(value, type, list);
        if (!list->Begin) return 1;

    }

    else {
        TListImpl *last = NULL;
        TListImpl *current = list->Begin;
        while (current->Next != NULL) {
            current = current->Next;
        }
        current->Next = AllocList(value, type, list);
    }
}

