//Стэк начало
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

int IsEmpty(TStack* List) {
    return !List->Begin;
}


//Стэк конец


int Add(ThreeNode *root, int val) {
    if (!root) {
        return 1;
    }
    if (root->value == val) {
        return 0;
    }
    if (root->value > val) {
        if (root->Left) {
            return Add(root->Left, val);
        }
        root->Left = (ThreeNode *)malloc(sizeof(ThreeNode*));
        root->Left->Left = NULL;
        root->Left->Right = NULL;
        root->Left->value = val;
    }
    if (root->value < val) {
        if (root->Right) {
            return Add(root->Right, val);
        }
        root->Right = (ThreeNode *)malloc(sizeof(ThreeNode*));
        root->Right->Left = NULL;
        root->Right->Right = NULL;
        root->Right->value = val;
    }
}

int WalkInVoid(ThreeNode *root) {
    TStack stack;
    Init(&stack);
    if (!root) {
        return 1;
    }
    Push(&stack, root);
    while (!IsEmpty(&stack)) {
        ThreeNode *cur;
        Pop(&stack, &cur);
        if (cur ->Left) {
            Push(&stack, cur->Left);
        }
        if (cur ->Right) {
            Push(&stack, cur->Right);
        }
    }
}