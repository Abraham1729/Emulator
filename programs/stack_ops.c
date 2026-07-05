#include <stdint.h>
#include "opcodes.h"
#include "vm.h"

int main(void) {
    /* Program to demonstrate the new stack manipulation opcodes */
    uint8_t program[] = {
        OP_PUSH, 1,
        OP_PUSH, 2,
        OP_DUP,
        OP_SWAP,
        OP_OVER,
        OP_PRINT,
        OP_DROP,
        OP_PRINT,
        OP_HALT
    };

    VM vm;
    vm_init(&vm, program, sizeof(program));
    vm_run(&vm);

    return 0;
}
