//
// Created by SeemS on 22.02.2026.
//
#include <stdio.h>
#include <ctype.h>
#include "haffman.h"

#ifndef LAB5_DECODER_H
#define LAB5_DECODER_H

int readBit(FILE *in, int *bit, unsigned char *currentByte, int *bitsLeft);

unsigned char readChar(FILE *in, unsigned char *currentByte, int *bitsLeft);

TreeNode *decodeTreeFromFile(FILE *file, unsigned char *currentByte, int *bitsLeft);

void decode(void);

#endif //LAB5_DECODER_H