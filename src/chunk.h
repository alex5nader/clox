#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_RETURN,
} Opcode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    ValueArray constants;

    int lineCount;
    int lineCapacity;
    int* lines;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);

int addConstant(Chunk* chunk, Value value);
void writeConstant(Chunk* chunk, Value value, int line);

int getLine(Chunk* chunk, int offset);

#endif //CLOX_CHUNK_H
