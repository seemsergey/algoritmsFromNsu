#include <stdio.h>

int solve() {
    char c = getchar();

    if (c == 't') {
        return 1;
    }
    if (c == 'f') {
        return 0;
    }

    if (c == '!') {
        getchar();
        int val = solve();
        getchar();

        return !val;
    }

    if (c == '&') {
        getchar();
        int res = 1;
        while (1) {
            int val = solve();
            res = res & val;
            char next = getchar();
            if (next == ')') {
                break;
            }
        }
        return res;
    }

    if (c == '|') {

        getchar();
        int res = 0;
        while (1) {
            int val = solve();
            res = res | val;
            char next = getchar();
            if (next == ')') {
                break;
            }
        }
        return res;

    }

    return 0;

}

int main(void) {

    if (solve()) {
        printf("t");
    } else {
        printf("f");
    }

    return 0;
}