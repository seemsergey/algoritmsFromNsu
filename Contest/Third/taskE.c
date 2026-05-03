#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void QuickSort(int *arr, int left, int right) {
    if (left >= right || left < 0) {
        return;
    }

    int i = left;
    int j = right;

    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) {
        QuickSort(arr, left, j);
    }
    if (i < right) {
        QuickSort(arr, i, right);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    QuickSort(a, 0, n - 1);
    int l[n], r[n];
    l[0] = a[0];
    r[0] = a[0];
    int masPos = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] + 1 == a[i + 1]) {
            r[masPos] = a[i + 1];
        } else {
            masPos += 1;
            l[masPos] = a[i + 1];
            r[masPos] = a[i + 1];
        }
    }
    masPos++;

    if (masPos == 1) {
        printf("%d", l[0]);
        return 0;
    }

    if (l[0] == r[0]) {

        printf("%d", l[0]);
    } else {

        printf("%d-%d", l[0], r[0]);
    }

    for (int i = 1; i < masPos; i++) {
        if (l[i] == r[i]) {
            printf(", %d", l[i]);
        } else {
            printf(", %d-%d", l[i], r[i]);
        }
    }

    return 0;
}