#include <stdio.h>
#include <stdlib.h>

int maxIndex(int *massive, int lenght) {
    // найти сколько волн всего(макс глуб дерева)
    int max = massive[0];
    int indx = 0;
    for (int i = 1; i < lenght; i++) {
        if (massive[i] > max) {
            max = massive[i];
            indx = i;
        }
    }
    return indx;
}


int lastWaveIs(int *massive, int lenght) {
    // глубина самого многочисленного поколения
    int i = 0;
    for (; i < lenght; i++) {
        if (massive[i] == 0) {
            break;
        }
    }
    return i - 1;
}

int getDepth(int curMember, int *depth, int *parent) {
    if (depth[curMember] != -1) {
        //если уже знаем глубину
        return depth[curMember];
    }

    if (parent[curMember] == -1) {
        // если надо выяснить, то батёк это корень
        return 0;
    }

    if (parent[curMember] != -1) {
        //если надо выяснить, но батёк рандом
        depth[curMember] = getDepth(parent[curMember], depth, parent) + 1; //то спросим его глубину у него, а он у деда
        return depth[curMember];
    }
}


int main(void) {
    int n; //кол-во человек
    scanf("%d", &n);
    int *parents = calloc(n, sizeof(int)); //массив с указанием кто чей батёк
    int *depth = malloc(sizeof(int) * n); // массив глубины каждого члена семьи
    int *wave = calloc((n+1), sizeof(int)); // кол-во человек на каждой глубине
    // => последнее i, где есть число - это максимальная глубина, а наибольшее поколение хранит наибольшее число в этом массиве
    for (int i = 0; i < n; i++) {
        scanf("%d", &parents[i]);
        depth[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int depthI = getDepth(i, depth, parents); // у каждого ищим рекурсивно глубину
        wave[depthI] += 1;
    }

    printf("%d %d", lastWaveIs(wave, n), maxIndex(wave, n));

    free(parents);
    free(depth);
    free(wave);
}
