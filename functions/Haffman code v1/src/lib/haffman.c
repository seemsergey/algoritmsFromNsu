//
// huffman.c - реализация дерева Хаффмана и кучи
//
#include "haffman.h"


TreeNode *createNode(unsigned char symbol, size_t freq, TreeNode *left, TreeNode *right, size_t height) {
    TreeNode *node = malloc(sizeof(TreeNode));
    if (!node) return NULL;
    node->ch = symbol;
    node->freq = freq;
    node->left = left;
    node->right = right;
    node->height = height;
    return node;
}

void clearTree(TreeNode *root) {
    if (root != NULL) {
        clearTree(root->left);
        clearTree(root->right);
        free(root);
    }
}

static void delHeapNode(int minIndex, TreeNode **heap, size_t *heapSize) {
    heap[minIndex] = heap[*heapSize - 1];
    (*heapSize)--;
}

void heapInsert(TreeNode **heap, size_t *heapSize, TreeNode *node) {
    heap[(*heapSize)++] = node;
}

TreeNode *minSearch(TreeNode **heap, size_t *heapSize) {
    if (*heapSize == 0) return NULL;
    int minIndex = 0;
    for (size_t i = 1; i < *heapSize; i++) {
        if (heap[i]->freq < heap[minIndex]->freq) {
            minIndex = (int)i;
        } else if (heap[i]->freq == heap[minIndex]->freq) {
            if (heap[i]->height < heap[minIndex]->height) {
                minIndex = (int)i;
            } else if (heap[i]->height == heap[minIndex]->height) {
                int isLeafI = (heap[i]->left == NULL && heap[i]->right == NULL);
                int isLeafMin = (heap[minIndex]->left == NULL && heap[minIndex]->right == NULL);
                if (!isLeafI && isLeafMin) {
                    minIndex = (int)i;
                } else if (isLeafI && isLeafMin) {
                    if (heap[i]->ch < heap[minIndex]->ch) {
                        minIndex = (int)i;
                    }
                }
            }
        }
    }
    TreeNode *minElem = heap[minIndex];
    delHeapNode(minIndex, heap, heapSize);
    return minElem;
}

// Построение внутреннего узла с гарантированным порядком left/right
void buildCodeTree(TreeNode **heap, size_t *heapSize) {
    TreeNode *a = minSearch(heap, heapSize);
    TreeNode *b = minSearch(heap, heapSize);

    TreeNode *left = a;
    TreeNode *right = b;

    // Если одинаковая частота, устанавливаем порядок: левый = меньший символ или лист
    if (a->freq == b->freq) {
        int aLeaf = (a->left == NULL && a->right == NULL);
        int bLeaf = (b->left == NULL && b->right == NULL);

        if (aLeaf && bLeaf && a->ch > b->ch) {
            left = b;
            right = a;
        } else if (!aLeaf && bLeaf) {
            left = b;
            right = a;
        } else if (aLeaf && !bLeaf) {
            left = a;
            right = b;
        }
    }

    size_t height = ((left->height > right->height) ? left->height : right->height) + 1;
    TreeNode *parent = createNode(0, left->freq + right->freq, left, right, height);
    heap[(*heapSize)++] = parent;
}

TreeNode *createHuffmanTree(TreeNode **heap, size_t *heapSize) {
    if (*heapSize == 0) return NULL;
    if (*heapSize == 1) return heap[0];

    while (*heapSize > 1) {
        buildCodeTree(heap, heapSize);
    }
    return heap[0];
}

void generateCodes(const TreeNode *root, HuffmanCode *codes, char *curCode, int lenCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch].ch = root->ch;
        curCode[lenCode] = '\0';
        strcpy(codes[root->ch].code, curCode);
        return;
    }
    curCode[lenCode] = '0';
    generateCodes(root->left, codes, curCode, lenCode + 1);
    curCode[lenCode] = '1';
    generateCodes(root->right, codes, curCode, lenCode + 1);
}
