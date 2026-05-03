#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long **matrix = malloc(n * sizeof(long long*));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(long long));
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &matrix[i][j]);
        }
    }
    
    long long targetSum = 0;
    for (int j = 0; j < n; j++) {
        targetSum += matrix[0][j];
    }
    
    // Проверяем все строки
    for (int i = 1; i < n; i++) {
        long long rowSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += matrix[i][j];
        }
        if (rowSum != targetSum) {
            printf("NO");
            return 0;
        }
    }
    
    // Проверяем все столбцы
    for (int j = 0; j < n; j++) {
        long long colSum = 0;
        for (int i = 0; i < n; i++) {
            colSum += matrix[i][j];
        }
        if (colSum != targetSum) {
            printf("NO");
            return 0;
        }
    }
    
    // Проверяем главную диагональ
    long long diag1 = 0;
    for (int i = 0; i < n; i++) {
        diag1 += matrix[i][i];
    }
    if (diag1 != targetSum) {
        printf("NO");
        return 0;
    }
    
    // Проверяем побочную диагональ
    long long diag2 = 0;
    for (int i = 0; i < n; i++) {
        diag2 += matrix[i][n-1-i];
    }
    if (diag2 != targetSum) {
        printf("NO");
        return 0;
    }
    
    printf("YES");
    
    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}