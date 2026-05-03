//
// Created by SeemS on 31.10.2025.
//

#include <stdio.h>

typedef struct {
    int x, y;
} possOfSegment;

int M, N;
int headX, headY, segmentX, segmentY;
int berryX, berryY;
int countOfMoves;
int length = 2;
int derection;
possOfSegment segment[2505]; //черезмерно большой, если на каждом шагу ягода
int movesHead[4][2] = {
    {-1, 0}, //влево = 0
    {0, 1}, //вверх = 1
    {1, 0}, //вправо = 2
    {0, -1} //вниз = 3
};


int isSnakeHere(int X, int Y) {
    for (int i = 0; i < length; i++) {
        if (segment[i].x == X && segment[i].y == Y) {
            return 1;
        }
    }
    return 0;
}

void UpdateBerry(int* bX, int* bY) {
    *bX = (*bX + 16127) % N;
    *bY = (*bY + 16843) % M;
    if (isSnakeHere(*bX, *bY)) {
        UpdateBerry(bX, bY);
    }
}

int moveSnake(int moveType) {
    int newX, newY;
    int lastTailX, lastTailY;
    lastTailX = segment[length-1].x;
    lastTailY = segment[length-1].y;
    newX = segment[0].x + movesHead[moveType][0];
    newY = segment[0].y + movesHead[moveType][1];
    if (newX < 0 || newX >= N || newY < 0 || newY >= M) {
        printf("Met wall\n");
        return 1;
    }
    if (isSnakeHere(newX, newY)) {
        printf("Met self\n");
        return 1;
    }

    for (int i = length-1; i > 0 ; i--) {
        segment[i] = segment[i - 1];
    }
    segment[0].x = newX;
    segment[0].y = newY;


    if (newX == berryX && newY == berryY) { //шоб не сломалось сначала двигаем, потом удлинняем
        segment[length].x = lastTailX;
        segment[length].y = lastTailY;
        length++;
        UpdateBerry(&berryX, &berryY);
    }
}

int main() {
    scanf("%d %d", &N, &M);
    scanf("%d %d", &headX, &headY);
    scanf("%d %d", &segmentX, &segmentY);
    scanf("%d %d", &berryX, &berryY);
    scanf("%d", &countOfMoves);

    segment[0].x = headX;
    segment[0].y = headY;
    segment[1].x = segmentX;
    segment[1].y = segmentY;

    //куда смотрит голова, чтобы не двигаться в себя же
    if (headX - segmentX == -1) {
        derection = 0; //влево
    } else if (headY - segmentY == 1) {
        derection = 1; //вверх
    } else if (headX - segmentX == 1) {
        derection = 2; //вправо
    } else if (headY - segmentY == -1) {
        derection = 3; //вниз
    }

    for (int i = 0; i < countOfMoves; i++) {
        int moveType;
        scanf("%d", &moveType);
        if (derection != moveType)
            moveSnake(moveType);
        else
            moveSnake(derection);
    }
    printf("%d", length);
}