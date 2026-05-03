#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int allTypes[10000] = {0};
    for (int i = 0; i < N; i++) {
        int type;
        scanf("%d", &type);
        allTypes[type - 1]++;
    }
    int a = 0, lastNOD = 0;
    for (int i = 0; i < 10000; i++) {
        if (allTypes[i] != 0) {
            if (lastNOD == 0) {
                lastNOD = allTypes[i];
            } else {
                a = allTypes[i];
                while (a != 0  && lastNOD != 0) {
                    if (a > lastNOD) {
                        a = a%lastNOD;
                    }
                    else {
                        lastNOD = lastNOD%a;
                    }
                }
                lastNOD = a + lastNOD;
            }
        }
    }
    printf("%d\n", lastNOD);
}
