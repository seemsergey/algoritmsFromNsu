#include <stdio.h>
#include <stdlib.h>

#define MAX_CELLS 1000001

unsigned char grid[1000][1000];
int island_sizes[500005];
int queue_x[MAX_CELLS];
int queue_y[MAX_CELLS];

int compare(const void *a, const void *b) {
    if (*(int *)a < *(int *)b) return 1;
    if (*(int *)a > *(int *)b) return -1;
    return 0;
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int val;
            scanf("%d", &val);
            grid[i][j] = (unsigned char)val;
        }
    }

    int island_count = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 1) {
                int current_size = 0;
                int head = 0, tail = 0;

                grid[i][j] = 0;
                queue_x[tail] = i;
                queue_y[tail] = j;
                tail++;
                current_size++;

                while (head < tail) {
                    int cx = queue_x[head];
                    int cy = queue_y[head];
                    head++;

                    if (cx > 0 && grid[cx - 1][cy] == 1) {
                        grid[cx - 1][cy] = 0;
                        queue_x[tail] = cx - 1;
                        queue_y[tail] = cy;
                        tail++;
                        current_size++;
                    }
                    if (cx < N - 1 && grid[cx + 1][cy] == 1) {
                        grid[cx + 1][cy] = 0;
                        queue_x[tail] = cx + 1;
                        queue_y[tail] = cy;
                        tail++;
                        current_size++;
                    }
                    if (cy > 0 && grid[cx][cy - 1] == 1) {
                        grid[cx][cy - 1] = 0;
                        queue_x[tail] = cx;
                        queue_y[tail] = cy - 1;
                        tail++;
                        current_size++;
                    }
                    if (cy < M - 1 && grid[cx][cy + 1] == 1) {
                        grid[cx][cy + 1] = 0;
                        queue_x[tail] = cx;
                        queue_y[tail] = cy + 1;
                        tail++;
                        current_size++;
                    }
                }
                island_sizes[island_count++] = current_size;
            }
        }
    }

    printf("%d\n", island_count);

    if (island_count > 0) {
        qsort(island_sizes, island_count, sizeof(int), compare);

        for (int i = 0; i < island_count; i++) {
            printf("%d ", island_sizes[i]);
        }
    } else {
        printf("\n");
    }

    return 0;
}