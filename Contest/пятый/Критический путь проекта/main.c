//
// Created by SeemS on 15.04.2026.
//
//кан->тп сорт -> прямой порядок-> обратный порядое ->если совпали, то задача критическая

#define MAXN 200005
#include <stdio.h>
#include <stdlib.h>
int duration[MAXN]; //длительность каждой задачи
int Earlier[MAXN]; //наименьшее время старта
int Latest[MAXN]; //самое позднее время старта
int inDegree[MAXN]; //кол-во входящих зависимостей у графа сейчас
int topology[MAXN]; //порядок топологической сортировки

int *adj[MAXN]; //матрица смежности
int adjN[MAXN]; //кол-во зависимостей вцелом у вершины
int adjCountMax[MAXN]; //кол-во выделеных мест сейчас




int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;


    for (int i = 0; i < N; i++) {
        int to = i;
        int dur = 0;
        scanf("%d", &dur);
        duration[i] = dur;
        int dependencyCount = 0;
        scanf("%d", &dependencyCount);
        inDegree[i] = dependencyCount;
        for (int j = 0; j < dependencyCount; j++) {
            int from;
            scanf("%d", &from);
            if (adjN[from] == adjCountMax[from]) {
                adjCountMax[from] = (adjCountMax[from] == 0) ? 2 : adjCountMax[from] * 2;
                adj[from] = realloc(adj[from], adjCountMax[from] * sizeof(int));
            }
            adj[from][adjN[from]++] = to;
        }
    }


    int head = 0, tail = 0;
    int queue[MAXN];

    for (int i = 0; i < N; i++) {
        if (inDegree[i] == 0) {
            queue[tail++] = i;
        }
    }

    int topoIndx = 0;
    while (head < tail) {
        int u = queue[head++]; //from
        topology[topoIndx++] = u;
        for (int i = 0; i < adjN[u]; i++) {
            int v = adj[u][i]; //to
            inDegree[v]--;
            if (inDegree[v] == 0) {
                queue[tail++] = v;
            }
            if (Earlier[u] + duration[u] > Earlier[v]) {
                Earlier[v] = Earlier[u] + duration[u];
            }
        }
    }

    int maxTime = 0; //прямая проходка чтобы получить самое ранее время начало задачи
    for (int i = 0; i < N; i++) {
        if (Earlier[i] + duration[i]> maxTime) {
            maxTime = Earlier[i] + duration[i];
        }
    }

    for (int i = 0; i < N; i++) {
        Latest[i] = maxTime;
    }
    //Самое позднее время начала каждой задачи(наибольший дедлайн из зависимых задач за минусом длительности)
    for (int i = N-1; i >= 0; i--) {
        int u = topology[i];

        if (adjN[u] == 0) { //типо нет зависимостей у проекта
            Latest[u] = maxTime - duration[u]; //самое позднее начало свободной задачи - конец дедлайна
        } else {
            int min_start_v = maxTime;
            for (int j = 0; j < adjN[u]; j++) { //смотрим на все задачи, которые пойдут после
                int v = adj[u][j];
                if (Latest[v] < min_start_v) { //найдём среди них минимальный дедлайн среди их дедлайнов
                    min_start_v = Latest[v]; //сохроняем
                }
            }
            Latest[u] = min_start_v - duration[u]; //наираньший поздний старт - мин. дедлайн минус длительность
        }
    }

    printf("%d\n", maxTime);
    int first = 1;
    for (int i = 0; i < N; i++) {
        if (Earlier[i] == Latest[i]) {
            if (!first) printf(" ");
            printf("%d", i);
            first = 0;
        }
    }
    printf("\n");

    return 0;

}