#include <stdint.h>
#include "opcodes.h"

static const uint8_t jump_demo_program[] = {
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
