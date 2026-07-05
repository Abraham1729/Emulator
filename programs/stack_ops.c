#include <stdint.h>
#include "opcodes.h"
#include "vm.h"

int main(void) {
    /* Program to demonstrate the new stack manipulation opcodes */
    /* Stack progression:
       push 1           -> [1]
       push 2           -> [1, 2]
       push 3           -> [1, 2, 3]
       swap             -> [1, 3, 2]
       print            -> pops 2, leaving [1, 3]
       drop             -> pops 3, leaving [1]
       push 4           -> [1, 4]
       swap             -> [4, 1]
       print            -> pops 1, leaving [4]
       print            -> pops 4, leaving []
       halt             -> stop
    */
    uint8_t program[] = {
        OP_PUSH, 1,
        OP_PUSH, 2,
        OP_PUSH, 3,
        OP_SWAP,
        OP_PRINT,
        OP_DROP,
        OP_PUSH, 4,
        OP_SWAP,
        OP_PRINT,
        OP_PRINT,
        OP_HALT
    };

    VM vm;
    vm_init(&vm, program, sizeof(program));
    vm_run(&vm);

    return 0;
}
