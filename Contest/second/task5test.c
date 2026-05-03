#include <stdio.h>

int F(int value, int position, int seed) {
    int result = 0;
    for (size_t i = 1; i <= seed * seed; ++i) {
        result = (result + (i % 2 ? value + 1 : position + 1) * i * seed) % 10;
    }
    return result;
}

int main() {
    int N;
    scanf("%d", &N);
    int seed;
    scanf("%d", &seed);
    int B;
    scanf("%d", &B);
    char A[7] = "2120104";
    for (int i = 0; i < 7; ++i) {
        printf("%d", F(A[i] - '0', i, seed));
    }
}