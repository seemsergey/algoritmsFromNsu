//
// Created by SeemS on 22.11.2025.
//

#include <stdio.h>


int main(){
    int n;
    scanf("%d", &n);
    long long sum, inpSum;
    sum = n*(n+1)/2;
    for (int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        inpSum += temp;
    }
    printf("%d", sum-inpSum);
}