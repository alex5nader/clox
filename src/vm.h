#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "table.h"
#include "value.h"

#define STACK_SIZE 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_SIZE];
    Value* stackTop;
    Table globals;
    Table strings;
    Obj* objects;
} VM;

extern VM vm;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM();
void freeVM();

InterpretResult interpret(char const* chunk);

void push(Value);
Value pop();

#endif // CLOX_VM_H
