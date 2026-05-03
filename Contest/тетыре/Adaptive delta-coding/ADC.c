#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 100000

char s[MAXN + 5];

int main() {
    scanf("%s", s);
    int n = strlen(s);

    int best_k = -1;
    int best_size = 0;

    for (int k = 1; k <= 9; k++) {
        int lastNum = 0;
        int pos = 0;
        int flag = 1;

        if ((n % k) != 0) {
            continue;
        }

        int count = n / k;

        unsigned char *buf = malloc(MAXN * 2);

        for (int i = 0; i < count; i++) {
            int start = i * k;

            if (k > 1 && s[start] == '0') {
                flag = 0;
                break;
            }

            int tempNum = 0;
            for (int j = 0; j < k; j++)
                tempNum = tempNum * 10 + (s[start + j] - '0');

            if (i == 0) {
                buf[pos++] = tempNum & 0xFF;
                buf[pos++] = (tempNum >> 8) & 0xFF;
            } else {
                int delta = tempNum - lastNum;
                if (delta >= -128 && delta <= 127) {
                    buf[pos++] = (unsigned char)delta;
                }
                else if (delta >= -32768 && delta <= 32767) {
                    int d = delta;
                    buf[pos++] = d & 0xFF;
                    buf[pos++] = (d >> 8) & 0xFF;
                }
                else {
                    flag = 0;
                    break;
                }
            }
            lastNum = tempNum;
        }

        if (!flag) {
            free(buf);
            continue;
        }

        if (best_k == -1 || pos < best_size) {
            best_size = pos;
            best_k = k;
        }

        free(buf);
    }

    if (best_k == -1) {
        printf("NO_SOLUTION");
        return 0;
    }
    int count = n / best_k;
    int lastNum = 0;


    printf("%d:", best_k);
    for (int i = 0; i < count; i++) {
        int start = i * best_k;

        if (best_k > 1 && s[start] == '0') {
            break;
        }

        int tempNum = 0;
        for (int j = 0; j < best_k; j++)
            tempNum = tempNum * 10 + (s[start + j] - '0');

        if (i == 0) {
            printf("%02x%02x ", tempNum & 0xFF, (tempNum >> 8) & 0xFF);
        } else {
            int delta = tempNum - lastNum;
            if (delta >= -128 && delta <= 127) {
                printf("%02x ", (unsigned char)delta);
            }
            else if (delta >= -32768 && delta <= 32767) {
                int d = delta;
                printf("%02x%02x ", d & 0xFF, (d >> 8) & 0xFF);
            }
            else {
                break;
            }
        }
        lastNum = tempNum;
    }

    return 0;
}