#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    unsigned int matrix[N][M];
    int angel;
    scanf("%d", &angel);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    switch (angel) {
        case 90:
            for (int i = 0; i < M; i++) {
                for (int j = N - 1; j > -1; j--) {
                    printf("%d ", matrix[j][i]);
                }
                printf("\n");
            }
            break;

        case 180:
            for (int i = N - 1; i > -1; i--) {
                for (int j = M - 1; j > -1; j--) {
                    printf("%d ", matrix[i][j]);
                }
                printf("\n");
            }
            break;

        case 270:
            for (int i = M - 1; i > -1; i--) {
                for (int j = 0; j < N; j++) {
                    printf("%d ", matrix[j][i]);
                }
                printf("\n");
            }
            break;

        default:
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    printf("%d ", matrix[i][j]);
                }
                printf("\n");
            }
            break;
    }

    return 0;
}