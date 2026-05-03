#include <stdio.h>

#define maxV 6
#define maxEdges 9
#define INF 9999999  // Убрали точки с запятой!
#define START_NODE 0 // A
#define END_NODE 5   // F (maxV - 1)

int C[maxV + 1]       = {0, 2, 5, 6, 7, 7, 9};
int R[maxEdges]       = {1, 2, 2, 3, 4, 3, 5, 2, 4};
int weights[maxEdges] = {2, 3, 1, 3, 5, 4, 2, -4, 6};

int main(void) {
    int table[maxV][2];

    for (int i = 0; i < maxV; i++) {
        table[i][0] = INF;
        table[i][1] = -1;
    }
    table[START_NODE][0] = 0;

    for (int k = 1; k < maxV; k++) { //номер итерации
        for (int u = 0; u < maxV; u++) {  //из какой идём
            if (table[u][0] == INF) continue;

            for (int j = C[u]; j < C[u + 1]; j++) { //куда идём
                int v = R[j];
                int weight = weights[j];
                if (table[u][0] + weight < table[v][0]) {
                    table[v][0] = table[u][0] + weight;
                    table[v][1] = u;
                }
            }
        }
    }

    printf("Кратчайшее расстояние от A(0) до F(%d) = %d\n", END_NODE, table[END_NODE][0]);

    printf("Путь (с конца): ");
    int cur = END_NODE;
    while (cur != -1) {
        printf("%c ", cur+'A');
        cur = table[cur][1];
    }
    printf("\n");

    return 0;
}