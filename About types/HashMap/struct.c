#include <stdlib.h>
#include <string.h>

typedef enum {
    Int,
    String,
    Float
} EValType;

typedef struct {
    char *key;
    EValType type;
    void *val;
    size_t size;
} TValue;

typedef size_t (*THashF)(char *key, void *ctx);

typedef struct {
    THashF HashF;
    void *Ctx;
} THashFDesc;

typedef struct {
    TValue *array;
    size_t capacity;
    size_t size;
    THashFDesc HashF;
} TBucket;

typedef struct {
    TBucket *Buckets;
    THashFDesc HashF;
    size_t capacity;
    size_t size;
} THashTable;

typedef struct {
    size_t A;
    size_t B;
    size_t P;
} TSimpleHashFCtx;

typedef struct {
    size_t E;
} THash2Ctx;

size_t HashFunc(char *key, void *ctx) {
    TSimpleHashFCtx *sCtx = (TSimpleHashFCtx *) ctx;
    size_t result = 0;
    for (int i = 0; i < strlen(key); ++i) {
        result = (result + key[i] * sCtx->A + sCtx->B) % sCtx->P;
    }
    return result;
}

size_t Hash2(char *key, void *ctx) {
    THash2Ctx *sCtx = (THash2Ctx *) ctx;
    return sCtx->E * key[0];
}

THashFDesc CreateSimpleHashF(size_t capacity) {
    TSimpleHashFCtx *ctx = (TSimpleHashFCtx *)malloc(sizeof(TSimpleHashFCtx));
    if (!ctx) {
        // Обработка ошибки выделения памяти (опционально)
        THashFDesc empty = {0};
        return empty;
    }

    ctx->A = (size_t)rand();
    ctx->B = (size_t)rand();
    ctx->P = capacity;

    THashFDesc result;
    result.HashF = HashFunc;
    result.Ctx = ctx;

    return result;
}

THashTable Create(size_t capacity) {
    static const size_t defaultBucketSize = 10;

    THashTable result;
    result.capacity = capacity;
    result.size = 0;

    result.Buckets = (TBucket *)malloc(capacity * sizeof(TBucket));

    result.HashF = CreateSimpleHashF(capacity);

    for (size_t i = 0; i < capacity; ++i) {
        TBucket *bucket = &result.Buckets[i];
        bucket->array = (TValue *)malloc(defaultBucketSize * sizeof(TValue));
        bucket->capacity = defaultBucketSize;
        bucket->size = 0;
    }

    return result;
}
int Add(THashTable* table, char *key, TValue val) {
    size_t hash = table->HashF.HashF(key, table->HashF.Ctx);
    TBucket *bucket = &table->Buckets[hash];

    if (bucket->size >= bucket->capacity) {
        bucket->capacity *= 2;
        bucket->array = (TValue *)realloc(bucket->array, bucket->capacity * sizeof(TValue));
    }
    for (size_t i = 0; i < bucket->size; ++i) {
        if (strcmp(bucket->array[i].key, key)) {
            val.val = bucket->array[i].val;
            bucket->array[i].key = key;
            return 0;
        }
    }

    bucket->array[bucket->size] = val;
    bucket->size++;
    table->size++;
    return 0;
}
int AddStr(THashTable table, char *key, void *value) {
    TValue v;
    v.val = value;
    v.size = strlen(value);
    v.type = String;
    v.key = key;
    return Add(&table, key, v);
}

