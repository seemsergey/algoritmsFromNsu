//
// Created by SeemS on 10.03.2026.
//


#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

long long v[MAXN];
long long dp[MAXN];
int chosen[MAXN];

int main() {
    int n = 0;
    while (scanf("%lld", &v[n]) == 1) {
        n++;
    }

    if (n == 0) return 0;

    dp[0] = v[0];
    if (n > 1) {
        if (v[1] > v[0]) {
            dp[1] =v[1];
        } else {
            dp[1] = v[0];
        }
    }

    for (int i = 2; i < n; i++) {
        if (v[i] + dp[i - 2] > dp[i - 1]) {
            dp[i] = v[i] + dp[i - 2];
        } else {
            dp[i] = dp[i - 1];
        }
    }

    // Вывод максимальной суммы
    printf("%lld\n", dp[n - 1]);


    int count = 0;
    int i = n - 1;
    while (i >= 0) {
        if (i == 0) {
            if (dp[0] == v[0]) {
                chosen[count++] = 0;
            }
            break;
        } else if (i == 1) {
            if (dp[1] == v[1]) {
                chosen[count++] = 1;
            } else {
                if (dp[0] == v[0]) {
                    chosen[count++] = 0;
                }
            }
            break;
        } else {

            if (dp[i] > dp[i - 1]) {
                chosen[count++] = i;
                i -= 2;
            } else {
                i -= 1;
            }
        }
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", chosen[i]);
    }

}