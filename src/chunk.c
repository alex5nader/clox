#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    *chunk = (Chunk) {
        .count = 0,
        .capacity = 0,
        .code = NULL,
        .lineCount = 0,
        .lineCapacity = 0,
        .lines = NULL,
    };

    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count += 1;

    if (chunk->lineCount > 0 && chunk->lines[chunk->lineCount - 1] == line) {
        chunk->lines[chunk->lineCount - 2] += 1;
    } else {
        if (chunk->lineCapacity < chunk->lineCount + 2) {
            int oldCapacity = chunk->lineCapacity;
            chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
            chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->lineCapacity);
        }

        chunk->lines[chunk->lineCount] = 1;
        chunk->lines[chunk->lineCount + 1] = line;
        chunk->lineCount += 2;
    }
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void writeConstant(Chunk* chunk, Value value, int line) {
    int constant = addConstant(chunk, value);

    if (((int) (uint8_t) constant) == constant) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, constant, line);
    } else {
        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, (uint8_t) constant, line);
        constant >>= 8;
        writeChunk(chunk, (uint8_t) constant, line);
        constant >>= 8;
        writeChunk(chunk, (uint8_t) constant, line);

        if (constant != 0) {
            exit(-1);
        }
    }
}

int getLine(Chunk* chunk, int offset) {
    int lineOffset = 0;

    for (int i = 0; i < chunk->lineCount; i += 2) {
        lineOffset += chunk->lines[i];

        if (lineOffset > offset) {
            return chunk->lines[i + 1];
        }
    }

    return -1;
}
