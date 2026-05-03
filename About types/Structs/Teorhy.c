//
// Created by SeemS on 11.10.2025.
//

#include <stdio.h>
#include <stdlib.h>

struct TMyStruct {
    int A;
    int B;
};
//внутри стуктуры нельзя написать int A = 1;



typedef struct { //структура на 8 байтиков
    int A;
    int B;
} TMySth;

typedef struct { //структура на 8 байтиков
    char A;
    int B;
} TSth;
//происходит выравнивание адресов -> char - 1 байт ----> int - 4 байта


typedef struct { //структура на 16 байтиков
    double z;
    int A;
    char B;
} TSth2;
//Z[????  ????]
//A[????][?***]B

typedef struct { //структура на 16 байтиков
    double z;
    int A;
    char B;
    char C;
} TSth3;
//Z[????  ????]
//A[????][??**]BC

typedef struct { //структура на 24 байтиков
    char B;
    char C;
    double z;
    int A;

} TSth4;
//[??******]BC
//[????????]Z
//[????****]



#pragma pack (push, 1)//1 - регулировка pading(того сколько * заполнителей будет)

#pragma pack (pop, 1)


//little ending - все маленькие байты в конце
//big ending - все маленькие байты в конце
//int  [????]
//l.e.: 3 - 0003
//b.e.: 3 - 3000


int main() {
    TMySth S;
    TMySth *B = (TMySth*)malloc(sizeof(TMySth));
    S.A = 1;
    S.B = 1;
    printf("%d %d", S.A, S.B);
    return 0;
}