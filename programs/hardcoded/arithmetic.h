#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdint.h>
#include "opcodes.h"

static const uint8_t arithmetic_program[] = {
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

#endif // ARITHMETIC_H