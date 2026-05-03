#include <stdio.h>

typedef union {
    unsigned char val;
    struct {
        unsigned char Writes_in_C_plus_plus : 1;  // бит 0
        unsigned char Writes_in_C : 1;            // бит 1
        unsigned char On_the_verge_of_expulsion : 1; // бит 2
        unsigned char Watched_anime : 1;          // бит 3
        unsigned char Slept_well : 1;             // бит 4
        unsigned char Ate_dumplings : 1;          // бит 5
        unsigned char Receives_a_scholarship : 1; // бит 6
        unsigned char Pass_exam : 1;              // бит 7
    } bits;
} Student;

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        Student student;
        int buf;
        scanf("%d", &buf);
        student.val = buf;
        if (student.bits.Writes_in_C_plus_plus || (student.bits.Pass_exam || student.bits.Receives_a_scholarship) && !(student.bits.Writes_in_C && student.bits.On_the_verge_of_expulsion)) {
            printf("1");
        }
        else {
            printf("0");
        }
    }

    return 0;
}