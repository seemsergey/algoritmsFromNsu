//
// Created by SeemS on 04.03.2026.
//


#include <stdio.h>

int main() {
    int W, n;

    if (scanf("%d %d", &W, &n) != 2) {
        return 0;
    }

    int dp[1001] = {0};

    for (int i = 0; i < n; i++) {
        int w, v, k;
        scanf("%d %d %d", &w, &v, &k);

        for (int weight = W; weight >= 0; weight--) {
            for (int l = 1; l <= k; l++) {
                int sumW = l * w;
                if (weight >= sumW) {
                    int curV = dp[weight - sumW] + l * v;
                    if (curV > dp[weight]) {
                        dp[weight] = curV;
                    }
                } else {
                    break;
                }
            }
        }
    }

    printf("%d\n", dp[W]);

    return 0;
}