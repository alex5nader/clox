#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "chunk.h"
#include "object.h"

#include <stdbool.h>

ObjFunction* compile(char const* source);

void markCompilerRoots();

#endif // CLOX_COMPILER_H
