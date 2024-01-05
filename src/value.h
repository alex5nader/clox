#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

#include "common.h"

typedef double Value;

void printValue(Value);

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray*);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray*);

#endif //CLOX_VALUE_H
