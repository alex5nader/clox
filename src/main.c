#include "common.h"
#include "chunk.h"
#include "debug.h"

// thank you https://www.shadertoy.com/view/WttXWX
unsigned int lowbias32(unsigned int x) {
    x ^= x >> 16;
    x *= 0x7feb352dU;
    x ^= x >> 15;
    x *= 0x846ca68bU;
    x ^= x >> 16;
    return x;
}

int main(int argc, char const* argv[]) {
    (void)argc;
    (void)argv;

    Chunk chunk;
    initChunk(&chunk);

    int line = 123;
    double value = 0.0;
    for (int i = 0; i < 300; i++) {
        writeConstant(&chunk, value, line);

        value += 3.5;
        if (lowbias32((unsigned int)i) % 5 == 0) {
            line += 1;
        }
    }

    writeChunk(&chunk, OP_RETURN, line);

    writeConstant(&chunk, 4.4, line);
    writeChunk(&chunk, OP_RETURN, line);

    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}