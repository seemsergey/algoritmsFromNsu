// Created by SeemS on 29.11.2025.
#define N 1000

int p[N];
int rank[N];

void MakeSet(int x) {
    p[x] = x;
    rank[x] = 0;
}

int FindSet(int x) {
    if (x == p[x])
        return x;
    return p[x] = FindSet(p[x]);

}

void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);
    if (x == y) return;

    if (rank[x] < rank[y]) {
        p[x] = y;
    } else if (rank[x] > rank[y]) {
        p[y] = x;
    } else {
        p[x] = y;
        rank[y]++;
    }
}