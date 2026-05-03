#include <stdio.h>

int stack[100] = {0};
int KS[100] = {0};

int max(int a, int b) {
    return (a > b) ? a : b;
}

void DFS(int N, int M, int graph[100][100], int from, int* counter,
         int is_T, int c, int arr[100], int in[100], int out[100]) {
    
    for (int i = 0; i < N; i++) {
        if (is_T && graph[i][from] == 0) continue;
        if (!is_T && graph[from][i] == 0) continue;

        if (arr[i] == 0) {
            arr[i] = 1;
            DFS(N, M, graph, i, counter, is_T, c, arr, in, out);
        } 
        else if (arr[i] == 1 && KS[i] != c && KS[i] != 0) {
            in[KS[i]]++; 
            out[c]++;
        }
    }

    if (!is_T) {
        stack[*counter] = from;
        (*counter)--;
    } else {
        KS[from] = c;
    }
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    int graph[100][100] = {0};
    int arr[100] = {0};
    int counter = N - 1;

    for (int i = 0; i < M; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        graph[from][to] = 1;
    }

    for (int i = 0; i < N; i++) {
        if (arr[i] == 0) {
            arr[i] = 1;
            DFS(N, M, graph, i, &counter, 0, 0, arr, NULL, NULL);
        }
    }

    for (int i = 0; i < N; i++) arr[i] = 0;
    
    int c = 1;
    int in[100] = {0}, out[100] = {0};

    for (int i = 0; i < N; i++) {
        int u = stack[i];
        if (arr[u] == 0) {
            arr[u] = 1;
            DFS(N, M, graph, u, &counter, 1, c, arr, in, out);
            c++;
        }
    }

    int ind = 0;
    int outd = 0;
    for (int i = 1; i < c; i++) {
        if (in[i] == 0) ind++;
        if (out[i] == 0) outd++;
    }

    if (c == 2) {
        printf("0");
    } else {
        printf("%d", max(ind, outd));
    }

    return 0;
}