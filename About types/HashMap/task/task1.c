//
// Created by SeemS on 06.12.2025.
//

#include <stdio.h>

#include"../struct.h"

int Check(); //проверяет наличие в таблице значение с

void ans(int array[N], int N) {
    THashTable table = Create(N);
    for (int i = 0; i < N; i++) {
        Add(table, array[i], array[i]);
        if (Check(&table, k-array[i])) {
            printf("%d - %d\n", array[i], array[k - array[i]]);
        }
    }
}

int main () {

}