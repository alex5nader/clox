#include "value.h"

#include "memory.h"

#include <stdio.h>

void printValue(Value value) {
    printf("%g", value);
}

void initValueArray(ValueArray* array) {
    *array = (ValueArray){
        .count = 0,
        .capacity = 0,
        .values = NULL,
    };
}

void writeValueArray(ValueArray* array, Value value) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count += 1;
}

void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}
