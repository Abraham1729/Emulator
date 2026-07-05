#include <stdio.h>
#include <stdint.h>
#include "opcodes.h"
#include "vm.h"

/* Assembled code */
int main(void) {
    /* Example program: push 5, push 3, add, print, halt */
    uint8_t program[] = {
        OP_PUSH, 5,
        OP_PUSH, 3,
        OP_ADD,
        OP_PRINT,
        OP_HALT
    };

    VM vm;
    vm_init(&vm, program, sizeof(program));
    vm_run(&vm);

    return 0;
}