#include <stdint.h>
#include "opcodes.h"
#include "vm.h"

int main(void) {
    /* Program to demonstrate the new stack manipulation opcodes */
    uint8_t program[] = {
        OP_PUSH, 1, /* -> [1] */
        OP_PUSH, 2, /* -> [1, 2] */
        OP_PUSH, 3, /* -> [1, 2, 3] */
        OP_SWAP,    /* -> [1, 3, 2] */
        OP_PRINT,   /* pops 2, leaving [1, 3] */
        OP_DROP,    /* pops 3, leaving [1] */
        OP_PUSH, 4, /* -> [1, 4] */
        OP_SWAP,    /* -> [4, 1] */
        OP_PRINT,   /* pops 1, leaving [4] */
        OP_PRINT,   /* pops 4, leaving [] */
        OP_HALT     /* stop */
    };

    VM vm;
    vm_init(&vm, program, sizeof(program));
    vm_run(&vm);

    return 0;
}
