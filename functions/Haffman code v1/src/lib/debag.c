//
// Created by SeemS on 22.02.2026.
//
/* --- ДЕБАГ --- */

#include <ctype.h>
#include <stdio.h>

#include "haffman.h"

#define INPUT_FILENAME  "in.my.txt"
#define OUTPUT_FILENAME "decoded.txt"


void debagOUT(void) {
    FILE *dbg = fopen(INPUT_FILENAME, "rb");
    if (!dbg) { perror("debug open"); return; }

    unsigned char b;
    printf("\nEncoded bytes (hex):\n");
    while (fread(&b, 1, 1, dbg) == 1) {
        printf("%02X ", b);
    }
    printf("\n\n");
    fclose(dbg);
}

/* --- ВЫВОД ДЕРЕВА --- */
void printHuffmanTree(TreeNode *root, int level, HuffmanCode *codes) {
    if (!root) return;

    // Отступ в зависимости от уровня вложенности
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    if (!root->left && !root->right) {
        // Это листовой узел
        if (isprint(root->ch)) {
            printf("'%c' (freq: %zu, 0x%02X)", root->ch, root->freq, root->ch);
        } else {
            printf("#%d (freq: %zu, 0x%02X)", root->ch, root->freq, root->ch);
        }

        // Добавляем вывод кода символа, если он существует
        if (codes[root->ch].code[0] != '\0') {
            printf(" -> %s", codes[root->ch].code);
        }

        printf("\n");
    } else {
        // Это внутренний узел
        printf("Node (freq: %zu, height: %zu)\n", root->freq, root->height);
    }

    // Рекурсивно выводим левое и правое поддеревья
    if (root->left) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("L: ");
        printHuffmanTree(root->left, level + 1, codes);
    }

    if (root->right) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("R: ");
        printHuffmanTree(root->right, level + 1, codes);
    }
}
