cmake_minimum_required(VERSION 3.26.4)

project(clox C)


set(SOURCES
        src/main.c
        src/chunk.c
        src/memory.c
        src/memory.h
        src/debug.c
        src/debug.h
        src/value.c
        src/value.h
        src/vm.c
        src/vm.h
        src/compiler.c
        src/compiler.h
        src/scanner.c
        src/scanner.h
        src/object.c
        src/object.h
        src/table.c
        src/table.h
)

add_executable(clox ${SOURCES})

set_property(TARGET clox PROPERTY C_STANDARD 99)
target_compile_options(clox
        PRIVATE
        -Wall
        -Werror
        -Wextra
)

