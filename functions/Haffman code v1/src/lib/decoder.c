//
// Created by SeemS on 22.02.2026.
//

/* --- ДЕКОДЕР --- */
#include "decoder.h"
#include "debag.h"

int readBit(FILE *in, int *bit, unsigned char *currentByte, int *bitsLeft) {
    if (*bitsLeft == 0) {
        if (fread(currentByte, 1, 1, in) != 1)
            return 0; // EOF
        *bitsLeft = 8;
        printf("[READ] New byte loaded: 0x%02X (binary: ", *currentByte);
        for (int i = 7; i >= 0; i--) {
            printf("%d", (*currentByte >> i) & 1);
        }
        printf(")\n");
    }
    *bit = (*currentByte >> 7) & 1;
    *currentByte <<= 1;
    (*bitsLeft)--;

    printf("[BIT] Read bit: %d | Bits left in current byte: %d\n", *bit, *bitsLeft);
    return 1;
}

unsigned char readChar(FILE *in, unsigned char *currentByte, int *bitsLeft) {
    unsigned char ch = 0;
    int bit;

    printf("[CHAR] Reading 8 bits for character:\n");
    for (int i = 0; i < 8; i++) {
        if (!readBit(in, &bit, currentByte, bitsLeft)) {
            printf("[ERROR] Unexpected end of file while reading character!\n");
            return 0;
        }
        ch = (ch << 1) | bit;
        printf("  Bit %d: %d | Current char state: 0x%02X\n", i, bit, ch);
    }

    if (isprint(ch)) {
        printf("[CHAR] Decoded character: '%c' (ASCII: %d, HEX: 0x%02X)\n", ch, ch, ch);
    } else {
        printf("[CHAR] Decoded control char: #%d (HEX: 0x%02X)\n", ch, ch);
    }
    return ch;
}

TreeNode *decodeTreeFromFile(FILE *file, unsigned char *currentByte, int *bitsLeft) {
    int bit;

    if (!readBit(file, &bit, currentByte, bitsLeft))
        return NULL;

    // Лист
    if (bit == 0) {
        printf("[TREE] Reading leaf node (bit=0)...\n");
        unsigned char ch = readChar(file, currentByte, bitsLeft);
        printf("[TREE] Created LEAF node: ");
        if (isprint(ch)) {
            printf("'%c' (freq: N/A)\n", ch);
        } else {
            printf("#%d (HEX: 0x%02X)\n", ch, ch);
        }
        return createNode(ch, 0, NULL, NULL, 0);
    }

    // Внутренний узел
    printf("[TREE] Reading INTERNAL node (bit=1)...\n");
    TreeNode *left = decodeTreeFromFile(file, currentByte, bitsLeft);
    TreeNode *right = decodeTreeFromFile(file, currentByte, bitsLeft);
    printf("[TREE] Combined INTERNAL node (left=%p, right=%p)\n", (void*)left, (void*)right);
    return createNode(0, 0, left, right, 0);
}

void decode(void) {
    FILE *inFile = stdin;
    if (!inFile) {
        perror("Cannot open input file");
        return;
    }

    FILE *outFile = stdout;
    if (!outFile) {
        perror("Cannot open output file");
        fclose(inFile);
        return;
    }

    size_t originalSize = 0;
    fread(&originalSize, sizeof(size_t), 1, inFile);
    printf("[DECODE] Original data size: %zu bytes\n", originalSize);

    // Инициализация состояния для чтения битов
    unsigned char currentByte = 0;
    int bitsLeft = 0;

    TreeNode *root = decodeTreeFromFile(inFile, &currentByte, &bitsLeft);

    size_t symbCount = 0;
    // currentByte = 0;
    // bitsLeft = 0;
    int count = 0;
    while (symbCount < originalSize) {
        TreeNode *node = root;

        while (node->left || node->right) {
            int bit;
            if (!readBit(inFile, &bit, &currentByte, &bitsLeft)) {
                break;
            }
            node = bit ? node->right : node->left;
        }
        count++;
        fputc(node->ch, outFile);

        symbCount++;
    }
    fprintf(stderr, "%d\n", count);

    clearTree(root);

    fclose(inFile);
    fclose(outFile);
}