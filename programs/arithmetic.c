#include <stdint.h>
#include "opcodes.h"
#include "vm.h"

int main(void) {
    /* Program to demonstrate arithmetic operations */
    /* Stack progression:
       push 5           -> [5]
       push 3           -> [5, 3]
       add              -> [8]
       push 10          -> [8, 10]
       push 2           -> [8, 10, 2]
       mul              -> [8, 20]
       sub              -> [-12]
       push 4           -> [-12, 4]
       div              -> [-3]
       print            -> prints -3
       halt             -> stop
    */
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
