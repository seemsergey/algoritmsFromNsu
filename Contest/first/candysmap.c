#include <stdio.h>

int main() {
    int n, m, q;
    static long long prefixMatrix[1000][1000];

    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            long long val;
            scanf("%lld", &val);

            prefixMatrix[i][j] = val;

            if (i > 0) prefixMatrix[i][j] += prefixMatrix[i-1][j];
            if (j > 0) prefixMatrix[i][j] += prefixMatrix[i][j-1];
            if (i > 0 && j > 0) prefixMatrix[i][j] -= prefixMatrix[i-1][j-1];
        }
    }

    // печать для проверки
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%lld ", prefixMatrix[i][j]);
        }
        printf("\n");
    }

    for (int k = 0; k < q; k++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--; y1--; x2--; y2--;

        long long ans = prefixMatrix[x2][y2];

        if (x1 > 0) ans -= prefixMatrix[x1-1][y2];
        if (y1 > 0) ans -= prefixMatrix[x2][y1-1];
        if (x1 > 0 && y1 > 0) ans += prefixMatrix[x1-1][y1-1];

        printf("%lld\n", ans);
    }

    return 0;
}
