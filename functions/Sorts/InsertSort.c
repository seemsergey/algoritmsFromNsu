//
// Created by SeemS on 08.11.2025.
//

#include <string.h>

void InsertSort(int *array, int length) {
    for (int i = 1; i < length; i++) {
        if (array[i] < array[i - 1]) {
            int j = 0;
            for ( j = 0 ; j < i; j++) {
                if (array[i] <= array[j]) { break; }
            }
            array[j] = array[i];
            memmove(&array[j+1], &array[j], (i - j - 1) * sizeof(int));
        }
    }
}
