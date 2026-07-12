#include <stdint.h>
#include "opcodes.h"
#include "vm.h"

int main(void) {
    /* Program to demonstrate arithmetic operations */
    uint8_t program[] = {
        OP_PUSH, 5,  /* -> [5] */
        OP_PUSH, 3,  /* -> [5, 3] */
        OP_ADD,      /* -> [8] */
        OP_PUSH, 10, /* -> [8, 10] */
        OP_PUSH, 2,  /* -> [8, 10, 2] */
        OP_MUL,      /* -> [8, 20] */
        OP_SUB,      /* -> [-12] */
        OP_PUSH, 4,  /* -> [-12, 4] */
        OP_DIV,      /* -> [-3] */
        OP_PRINT,    /* prints -3 */
        OP_HALT      /* stop */
    };

    VM vm;
    vm_init(&vm, program, sizeof(program));
    vm_run(&vm);

    return 0;
}
