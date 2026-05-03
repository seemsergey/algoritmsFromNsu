#include <stdio.h>
#include <string.h>

int xCost, yCost, zCost, tCost, maxDist;

int min(int n1, int n2) {
    return (n1 < n2 ? n1 : n2);
}

int builDamerauLevenshteinDistance(char origin[], char suggestion[]) {
    int m = strlen(suggestion);
    int n = strlen(origin);

    int prev2[m + 1];
    int prev1[m + 1];
    int cur[m + 1];

    for (int j = 0; j <= m; j++) {
        prev1[j] = j * zCost;
    }

    if (n == 0) return prev1[m];

    for (int i = 1; i <= n; i++) {
        cur[0] = i * yCost;
        for (int j = 1; j <= m; j++) {
            int cost = (origin[i - 1] == suggestion[j - 1]) ? 0 : xCost;

            int del = prev1[j] + yCost;
            int ins = cur[j - 1] + zCost;
            int repl = prev1[j - 1] + cost;
            int minD = min(min(del, ins), repl);

            // Транспозиция
            if (i > 1 && j > 1 &&
                origin[i - 2] == suggestion[j - 1] &&
                suggestion[j - 2] == origin[i - 1]) {
                int transp = prev2[j - 2] + tCost;
                minD = min(minD, transp);
            }
            cur[j] = minD;
        }
        memcpy(prev2, prev1, sizeof(int) * (m + 1));
        memcpy(prev1, cur, sizeof(int) * (m + 1));
    }
    return prev1[m];
}

int main(void) {
    char orig[505];
    if (scanf("%504s", orig) != 1) return 0;
    
    int k;
    if (scanf("%d", &k) != 1) return 0;
    
    char dict[105][505];
    for (int i = 0; i < k; i++) {
        scanf("%504s", dict[i]);
    }

    if (scanf("%d %d %d %d %d", &xCost, &yCost, &zCost, &tCost, &maxDist) != 5) return 0;
    
    int minDist = -1;
    int dists[105];
    
    for (int i = 0; i < k; i++) {
        dists[i] = builDamerauLevenshteinDistance(orig, dict[i]);
        if (minDist == -1 || dists[i] < minDist) {
            minDist = dists[i];
        }
    }
    
    if (minDist == -1 || minDist > maxDist) {
        printf("NO_CORRECTION\n");
    } else {
        for (int i = 0; i < k; i++) {
            if (dists[i] == minDist) {
                printf("%s\n", dict[i]);
            }
        }
    }
    
    return 0;
}