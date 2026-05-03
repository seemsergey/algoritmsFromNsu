//
// Created by SeemS on 11.10.2025.
//

#include <stdio.h>
typedef union TUn { //8 байт
    double f;
    long g; //даже если тут int, то 8

} TUn;

typedef union TUn2 { //8 байт
    char s;
    struct {
        char a:1;
        char b:2;
        char c:3;
        char d:2;
    };
} TUn2;


int main() {
    TUn x;
    x.f = 987654321.23123312;
    printf("%d\n", sizeof(TUn));
    printf("%f\n", x.f);
    printf("%ld\n", x.g);
}