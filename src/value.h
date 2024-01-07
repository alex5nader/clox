#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
    VAL_OBJ,
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
        Obj* obj;
    } as;
} Value;

#define BOOL_VAL(value)   ((Value){.type = VAL_BOOL, .as.boolean = value})
#define NIL_VAL           ((Value){.type = VAL_NIL})
#define NUMBER_VAL(value) ((Value){.type = VAL_NUMBER, .as.number = value})
#define OBJ_VAL(value)    ((Value){.type = VAL_OBJ, .as.obj = (Obj*) value})

#define IS_BOOL(value)   ((value).type == VAL_BOOL)
#define IS_NIL(value)    ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)
#define IS_OBJ(value)    ((value).type == VAL_OBJ)

#define AS_BOOL(value)   ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)
#define AS_OBJ(value)    ((value).as.obj)

void printValue(Value);
bool valuesEqual(Value, Value);

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray*);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray*);

#endif // CLOX_VALUE_H
