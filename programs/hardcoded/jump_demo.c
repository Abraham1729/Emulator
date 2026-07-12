#include <stdint.h>
#include "opcodes.h"
#include "vm.h"

int main(void) {
    /* Program to demonstrate that JUMP can skip and return to instructions */
    uint8_t program[] = {
        OP_PUSH, 1,      /* push the first value: [1] */
        OP_JUMP, 0x05,   /* skip over the middle block and go to the print */
        OP_HALT,         /* this instruction is skipped by the jump */
        OP_PRINT,        /* print the value that is still on the stack: 1 */
        OP_JUMP, 0x09,   /* jump forward into the arithmetic block */
        OP_DROP,         /* this instruction is skipped by the jump */
        OP_PUSH, 2,      /* push 2: [2] */
        OP_PUSH, 3,      /* push 3: [2, 3] */
        OP_ADD,          /* add them: [5] */
        OP_PRINT,        /* print the result: 5 */
        OP_JUMP, 0x04,   /* jump back to the halt instruction */
    };

    VM vm;
    vm_init(&vm, program, sizeof(program));
    vm_run(&vm);

    return 0;
}
