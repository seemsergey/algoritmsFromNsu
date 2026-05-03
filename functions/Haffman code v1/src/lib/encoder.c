//
// Created by SeemS on 22.02.2026.
//
#include "encoder.h"
#include "config.h"
#include "debag.h"
#include <ctype.h>  // Добавляем для isprint()

/* --- КОДИРОВЩИК --- */
void writeByte(FILE *out, int bit, unsigned char *byte, int *count) {
    *byte = (*byte << 1) | bit;
    (*count)++;
    if (*count == 8) {
        fwrite(byte, 1, 1, out);
        *count = 0;
        *byte = 0;
    }
}

void writeTreeIntoFile(const TreeNode *root, FILE *file, int *bitCount, unsigned char *outByte) {
    if (!root) return;
    if (!root->left && !root->right) {
        writeByte(file, 0, outByte, bitCount);
        for (int i = 7; i >= 0; i--) {
            writeByte(file, (root->ch >> i) & 1, outByte, bitCount);
        }
        return;
    }
    writeByte(file, 1, outByte, bitCount);
    writeTreeIntoFile(root->left, file, bitCount, outByte);
    writeTreeIntoFile(root->right, file, bitCount, outByte);
}

void encode(void) {
    unsigned char *data = NULL;
    size_t size = 0, cap = 0;
    int c;

    /* --- ДОБАВЛЕННЫЙ ДЕБАГ: Инициализация для статистики --- */
    size_t charFreq[ALPHABET_SIZE] = {0};
    printf("=== START OF DEBUG OUTPUT ===\n");
    printf("Reading input characters:\n");
    /* ----------------------------- */

    while ((c = getchar()) != EOF) {
        if (size == cap) {
            size_t new_cap = cap ? cap * 2 : 1024;
            unsigned char *new_data = realloc(data, new_cap);
            if (!new_data) {
                free(data);
                perror("Memory allocation failed");
                return;
            }
            data = new_data;
            cap = new_cap;
        }
        data[size++] = (unsigned char)c;

        /* --- ДОБАВЛЕННЫЙ ДЕБАГ: Вывод каждого символа --- */
        charFreq[(unsigned char)c]++;

        if (isprint(c)) {
            printf("  Read: '%c' | Hex: 0x%02X | Decimal: %d | Total: %zu\n",
                   c, (unsigned char)c, c, charFreq[(unsigned char)c]);
        } else {
            printf("  Read: non-printable | Hex: 0x%02X | Decimal: %d | Total: %zu\n",
                   (unsigned char)c, c, charFreq[(unsigned char)c]);
        }
        /* ------------------------------------------- */
    }

    if (!size) {
        free(data);
        return;
    }

    /* --- ДОБАВЛЕННЫЙ ДЕБАГ: Итоговая статистика --- */
    printf("\nCharacter frequency summary:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (charFreq[i] > 0) {
            if (isprint(i)) {
                printf("  '%c': 0x%02X | Count: %zu\n", i, i, charFreq[i]);
            } else {
                printf("  non-printable: 0x%02X | Count: %zu\n", i, charFreq[i]);
            }
        }
    }
    printf("\nTotal characters read: %zu\n", size);
    printf("=== END OF DEBUG OUTPUT ===\n\n");
    /* ------------------------------------------- */

    size_t freq[ALPHABET_SIZE] = {0};
    for (size_t i = 0; i < size; i++)
        freq[data[i]]++;

    /* -------- строим кучу -------- */
    TreeNode *heap[ALPHABET_SIZE];
    size_t heapSize = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > 0) {
            TreeNode *node = createNode((char)i, freq[i], NULL, NULL, 0);
            heapInsert(heap, &heapSize, node);
        }
    }
    TreeNode *root = createHuffmanTree(heap, &heapSize);

    HuffmanCode codes[ALPHABET_SIZE] = {0};
    char curCode[ALPHABET_SIZE];
    generateCodes(root, codes, curCode, 0);

    // Выводим структуру дерева Хаффмана с кодами
    printf("\n=== Huffman Tree Structure (Encoder) ===\n");
    printHuffmanTree(root, 0, codes);
    printf("========================================\n");

    FILE *out = stdout;
    if (!out) { perror("open archive"); free(data); return; }
    fwrite(&size, sizeof(size_t), 1, out);
    unsigned char outByte = 0;
    int bitCount = 0;
    writeTreeIntoFile(root, out, &bitCount, &outByte);
    // if (bitCount != 0) {
    //     outByte <<= (8 - bitCount);
    //     fwrite(&outByte, 1, 1, out);
    // }
    // outByte = 0;
    // bitCount = 0;
    for (size_t i = 0; i < size; i++) {
        char *code = codes[data[i]].code;
        for (int j = 0; code[j]; j++) {
            writeByte(out, code[j] == '1', &outByte, &bitCount);
        }
    }

    // ИСПРАВЛЕНИЕ: убрать дублирование
    if (bitCount != 0) {
        outByte <<= (8 - bitCount);
        fwrite(&outByte, 1, 1, out);
    }

    // Освобождаем память
    clearTree(root);
    free(data);
    fclose(out);
}