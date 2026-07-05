#include <stdio.h>
#include <stdint.h>
#include "opcodes.h"
#include "vm.h"

int main(void) {
    // Program to demonstrate the virtual machine operations
    // ADD: 5 + 3 = 8
    // MUL: 10 * 2 = 20
    // SUB: 8 - 20 = -12
    // DIV: -12 / 4 = -3
    // PRINT: -3
    
    uint8_t program[] = {
        OP_PUSH, 5,
        OP_PUSH, 3,
        OP_ADD,
        OP_PUSH, 10,
        OP_PUSH, 2,
        OP_MUL,
        OP_SUB,
        OP_PUSH, 4,
        OP_DIV,
        OP_PRINT,
        OP_HALT
    };

    VM vm;
    vm_init(&vm, program, sizeof(program));
    vm_run(&vm);

    return 0;
}