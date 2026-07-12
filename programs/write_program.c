// Need to write raw bytes to file in same directory so I can demonstrate that run_program works as intended //
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"
#include "bytefiles.h"

int main(void) {
    // Example byte array to write to file
    uint8_t bytes[] = {
        OP_PUSH, 1,    // PUSH 1 -> [1]
        OP_PUSH, 3,    // PUSH 3 -> [1, 3]
        OP_ADD,        // ADD -> [4]
        OP_PUSH, 7,    // PUSH 7 -> [4, 7]
        OP_PUSH, 2,    // PUSH 2 -> [4, 7, 2]
        OP_SUB,        // SUB -> [4, 5]
        OP_PRINT,      // PRINT -> prints 5
        OP_PRINT,      // PRINT -> prints 4
        OP_HALT        // HALT
    };
    size_t length = sizeof(bytes) / sizeof(bytes[0]);

    write_bytes_to_file("output/program.bin", bytes, length);

    printf("Wrote %zu bytes to output/program.bin\n", length);
    return 0;
}