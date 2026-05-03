//
// Created by SeemS on 08.11.2025.
//

void BubbleSort(int *array, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-i; ++j) {
            if (array[i] > array[j]) {
                array[j] = array[i] + array[j];
                array[i] = array[j] - array[i];
                array[j] = array[j] - array[i];
            }
        }
    }
}