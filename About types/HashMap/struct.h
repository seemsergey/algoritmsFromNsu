#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>

// Типы значений
typedef enum {
    Int,
    String,
    Float
} EValType;

// Структура значения с ключом
typedef struct {
    char *key;
    EValType type;
    void *val;
    size_t size;
} TValue;

// Тип хеш-функции
typedef size_t (*THashF)(char *key, void *ctx);

// Описание хеш-функции (указатель + контекст)
typedef struct {
    THashF HashF;
    void *Ctx;
} THashFDesc;

// Бакет (список коллизий)
typedef struct {
    TValue *array;
    size_t capacity;
    size_t size;
    THashFDesc HashF; // обычно не нужен, но оставлен по вашей структуре
} TBucket;

// Хеш-таблица
typedef struct {
    TBucket *Buckets;
    THashFDesc HashF;
    size_t capacity;
    size_t size;
} THashTable;

// Контексты хеш-функций
typedef struct {
    size_t A;
    size_t B;
    size_t P;
} TSimpleHashFCtx;

typedef struct {
    size_t E;
} THash2Ctx;

// Функции (только объявления!)
THashFDesc CreateSimpleHashF(size_t capacity);

THashTable Create(size_t capacity);

int Add(THashTable *table, char *key, TValue val);

int AddStr(THashTable *table, char *key, void *value);

// Дополнительно (рекомендуется для полноты):
void Destroy(THashTable *table);

#endif // HASHTABLE_H