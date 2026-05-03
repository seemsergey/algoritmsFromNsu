//
// Created by SeemS on 08.11.2025.
//

void heapify(int i, int *array, int n); //превращает в кучу поддерево с номером i
void sift_down(int i, int *array, int n); //просеивает вершину i вних по правилам кучи
void swap(int *arr1, int *arr2);

void sift_down(int i, int *array, int n) {
    if (i >= n) {return;}
    int largestPos = i;
    int largestNum = array[i];
    if (i * 2 + 1 < n && largestNum > array[i * 2]) {
        largestPos = i * 2 + 1;
        largestNum = array[i * 2 + 1];
    }
    int rightPos = 2 * i + 2;
    if (rightPos < n && array[rightPos] > largestNum) {
        largestPos = rightPos;
        largestNum = array[rightPos];
    }
    if (i != largestPos) {
        swap(&array[i], &array[largestPos]);
        sift_down(largestPos, array, n);
    }
}

void heapify(int i, int *array, int n) { //выолнится за O(n)
    for (int j = n/2-1; j >= i; --j) {
        sift_down(j, array, n);
    }
}

void sift_up(int i, int *array, int n) {

}
void Pop();