#include <stdio.h>
#include <string.h>

int F(int value, int position, int seed) {
    int result = 0;
    for (size_t i = 1; i <= (size_t)seed * seed; ++i) {
        result = (result + (i % 2 ? value + 1 : position + 1) * i * seed) % 10;
    }
    return result;
}


void dfs(int pos, int *found, char result[205], int possible[205][10], int N) {
    if (*found >= 5) return;
    if (pos == N) {
        result[N] = '\0';
        printf("%s\n", result);
        (*found)++;
        return;
    }
    // идём от 9 к 0, чтобы сначала были лексикографически большие
    for (int d = 9; d >= 0; --d) {
        if (possible[pos][d]) {
            result[pos] = '0' + d;
            dfs(pos + 1, found, result, possible, N);
            if (*found >= 5) return;
        }
    }
}

int main() {
    int N, seed;
    char B[205];
    int possible[205][10];
    int found = 0;
    char result[205];

    if (scanf("%d %d %s", &N, &seed, B) != 3) return 0;


    for (int pos = 0; pos < N; ++pos) {
        for (int d = 0; d < 10; ++d) {
            int f = F(d, pos, seed);
            if (f == B[pos] - '0')
                possible[pos][d] = 1;
            else
                possible[pos][d] = 0;
        }
    }

    dfs(0, &found, result, possible, N);

    if (found == 0)
        printf("No solutions\n");

    return 0;
}
