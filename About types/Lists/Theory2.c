//обычный односвязный список

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
    TListImpl *End;
    int Size;
} TList;

TListImpl *AllocList(TUn value, EType type) {
    TListImpl *el = (TListImpl *) malloc(sizeof(TListImpl));
    el->Value = value;
    el->Type = type;
    el->Next = NULL;
    return el;
}


void Push(TList *list, TUn value, EType type) {
    if (!list->Begin) {
        list->Begin = AllocList(value, type, list);
        list->End = list->Begin;
    }
    else{
        list->End->Next = AllocList(value, type, list);
        list->End = list->End->Next;
    }

}

int Pop(TList *list, TUn *value, EType *type) {
    if (list->Begin == NULL) {
        return 1;
    }
    TListImpl *current = list->Begin;

    while (current->Next != NULL && current->Next->Next == NULL) {
        current = current->Next;
    }
    if (current->Next == NULL) {
        free(current);
        list->Begin = NULL;
        list->End = NULL;
        return 0;
    }
    *value = current->Next->Value;
    *type = current->Next->Type;
    free(current->Next);
    list->End = current;
    // list->Next = NULL;
    return 0;

}

int Delete(TList *list, TUn value, EType type, int i) {
    if (!list)
        return 1;
    if (!list->Begin)
        return 1;
    TListImpl *current = list->Begin;
    int j = 0;
    while (j != i-1 && current->Next != NULL && current->Next->Next != NULL) {
        current = current->Next;
        j++;
    }
    if (current->Next == NULL) {
        if (j == 0) {
            free(current);
            list->Begin = NULL;
        } else {
            return 1;
        }
        if (j == i) {
            TListImpl *buf = current->Next->Next;
            free(current->Next);
            current->Next = buf -> Next;
            return 0;
        } else {
            return 1;
        }
    }

}