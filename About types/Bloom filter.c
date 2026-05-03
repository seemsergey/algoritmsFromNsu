// Created by SeemS on 29.11.2025.
#include <stdio.h>
#include <string.h>

#define M 10   // размер фильтра Блума
#define K 3    // количество хеш-функций (уменьшено для примера)

unsigned char bloom[M]; // используем unsigned char или bool (C99+)

// Пример простой хеш-функции (в реальности нужны хорошие независимые хеши!)
// Возвращает значение в [0, M-1]
int h(int x, int i) {
    // Простой пример: можно заменить на настоящие хеш-функции
    // Например: (a_i * x + b_i) % prime % M
    return (x * (i + 1) + i * 37) % M;
}

void add(int x) {
    for (int i = 0; i < K; ++i) {
        int idx = h(x, i);
        bloom[idx] = 1;
    }
}

int check(int x) {
    for (int i = 0; i < K; ++i) {
        int idx = h(x, i);
        if (!bloom[idx])
            return 0; // элемент точно НЕ в множестве
    }
    return 1; // элемент, возможно, в множестве (может быть ложное срабатывание)
}

// Инициализация фильтра
void bloom_clear() {
    memset(bloom, 0, sizeof(bloom));
}

// Пример использования
int main() {
    bloom_clear();
    add(42);
    add(100);

    printf("Check 42: %d\n", check(42));   // → 1
    printf("Check 99: %d\n", check(99));   // → 0 (скорее всего)
    printf("Check 200: %d\n", check(200)); // → возможно 1 (ложное срабатывание)

    return 0;
}