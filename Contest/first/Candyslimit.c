#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 0;
    long long S = 0; // S должно быть long long
    scanf("%d %lld", &n, &S);

    int *shelf = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &shelf[i]);
    }

    int maxLen = 0, l = 0;
    long long currentSumm = 0, bestSumm = 0;

    for (int r = 0; r < n; r++) {
        currentSumm += shelf[r];
        while (currentSumm > S && l <= r) {
            currentSumm -= shelf[l];
            l++;
        }
        if (maxLen < r - l + 1) {
            maxLen = r - l + 1;
            bestSumm = currentSumm;
        }
    }

    printf("%d\n%lld\n", maxLen, bestSumm);

    free(shelf);
    return 0;
}
