#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *a = malloc(100002 * sizeof(char));
    char *b = malloc(100002 * sizeof(char));
    fgets(a, 100002, stdin);
    fgets(b, 100002, stdin);
    int aLen = strlen(a) - 1;
    int bLen = strlen(b) - 1;

    int mSize = 0;
    if (aLen >= bLen) {
        mSize = aLen;
    } else {
        mSize = bLen;
    }
    //printf("%s - %d, %s - %d, %d \n", a, aLen, b, bLen, mSize);
    char *result = calloc(mSize + 2, sizeof(char));

    short int carry = 0;
    for (int i = 0; i < mSize; i++) {
        int sum = carry;
        if (aLen - i > 0) {
            sum += a[aLen - 1 - i] - '0';
        }
        if (bLen - i > 0) {
            sum += b[bLen - 1 - i] - '0';
        }
        result[i] = sum % 10 + '0';
        carry = sum / 10;
    }
    free(a);
    free(b);
    if (carry) {
        result[mSize] = carry+'0';
        mSize++;
    }

    for (int i = mSize - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }

    free(result);

    return 0;
}
