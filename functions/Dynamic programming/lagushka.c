//
// Created by SeemS on 11.02.2026.
//


#include <stdio.h>
//Нисходящий вариант
int Kva(int n, int end) {
    if (end == n) return 1;
    if (end < n) return 0;
    return Kva(n+1, end) + Kva(n+2, end);
}

//Восходящий вариант(Как фибоначи)
int KvaV2(int end) {

}


int main() {
    int endPoint = 0;
    scanf("%d", &endPoint);
    printf("%d", Kva(1, endPoint));
}
