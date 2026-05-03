//
// Created by SeemS on 27.02.2026.
//

#include <stdio.h>
#include <string.h>

int main(void) {
    int windowSize, bufferSize;
    scanf("%d %d", &windowSize, &bufferSize); // Считываем настройки!

    char s[10005];
    scanf("%s", s); // Считываем строку

    int lens = strlen(s);
    int pos = 0;

    while (pos < lens) {
        int offset = 0;
        int length = 0;

        for (int curOffset = 1; curOffset <= windowSize && curOffset <= pos; curOffset++) { //мы не должны выйти за пределы окна, что дала задача и не должный уйти дальше позиции
            int curlength = 0;
            while (curlength < bufferSize && pos + curlength < lens && s[pos - curOffset + curlength] == s[pos + curlength]) {
                curlength++;
            }
            if (curlength > length) {
                length = curlength;
                offset = curOffset;
            }
        }

        if (pos + length == lens) {
            printf("(%d,%d,\\0)\n", offset, length);
            pos += length;
        } else {
            char nextChar = s[pos + length];
            printf("(%d,%d,%c)\n", offset, length, nextChar);
            pos += length + 1;
        }
    }

    return 0;
}
