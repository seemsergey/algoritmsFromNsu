//
// Created by SeemS on 22.02.2026.
//
#include <stdio.h>
#include "haffman.h"
#include <stdlib.h>

#ifndef LAB5_ENCODER_H
#define LAB5_ENCODER_H

void writeByte(FILE *out, int bit, unsigned char *byte, int *count);

void writeTreeIntoFile(const TreeNode *root, FILE *file, int *bitCount, unsigned char *outByte);

void encode(void);

#endif //LAB5_ENCODER_H