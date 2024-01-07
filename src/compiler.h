#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "chunk.h"

#include <stdbool.h>

typedef enum {
    COMPILE_OK = true,
    COMPILE_ERROR = false,
} CompileResult;

CompileResult compile(char const* source, Chunk* chunk);

#endif // CLOX_COMPILER_H
