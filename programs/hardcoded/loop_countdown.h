#ifndef LOOP_COUNTDOWN_H
#define LOOP_COUNTDOWN_H

#include <stdint.h>
#include "opcodes.h"

static const uint8_t loop_countdown_program[] = {
    // Initialize the countdown value //
    OP_PUSH, 5,      /* -> [5] */

    // Loop Start: Check if the countdown value is zero //
    OP_DUP,          /* -> [i, i] */
    OP_PRINT,        /* pops one i, leaving [i] */

    // Decrement the countdown value //
    OP_PUSH, 1,      /* -> [i, 1] */
    OP_SUB,          /* -> [i-1] */

    // Halt if the countdown value is zero, otherwise loop back //
    OP_DUP,          /* -> [i-1, i-1] */
    OP_JMPZ, 0x0C,   /* if the top copy is 0, jump to halt */
    OP_JUMP, 0x02,   /* otherwise loop back to the duplicate step */
    OP_HALT          /* stop */
};

#endif // LOOP_COUNTDOWN_H