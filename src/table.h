#ifndef CLOX_TABLE_H
#define CLOX_TABLE_H

#include "common.h"
#include "value.h"

typedef struct {
    ObjString* key;
    Value value;
} Entry;

typedef struct {
    int count;
    int capacity;
    Entry* entries;
} Table;

void initTable(Table*);
void freeTable(Table*);

bool tableGet(Table*, ObjString* key, Value* value);
bool tableSet(Table*, ObjString* key, Value value);
bool tableDelete(Table*, ObjString* key);
void tableAddAll(Table* src, Table* dest);
ObjString* tableFindString(Table*, char const* chars, int length, uint32_t hash);

#endif // CLOX_TABLE_H
