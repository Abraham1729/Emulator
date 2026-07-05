#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

/* Operation codes for the virtual machine */
typedef enum {
    OP_HALT  = 0x00, /* halt execution */
    OP_PUSH  = 0x01, /* push 1-byte-literal onto the stack */
    OP_DROP  = 0x02, /* remove the top stack value */
    OP_DUP   = 0x03, /* duplicate the top stack value */
    OP_SWAP  = 0x04, /* swap the top two stack values */
    OP_OVER  = 0x05, /* duplicate the second item on the stack */
    OP_ADD   = 0x06, /* pop 2 values from the stack, add them, and push the result */
    OP_SUB   = 0x07, /* pop 2 values from the stack, subtract the second from the first, and push the result */
    OP_MUL   = 0x08, /* pop 2 values from the stack, multiply them, and push the result */
    OP_DIV   = 0x09, /* pop 2 values from the stack, divide the second by the first, and push the result */
    OP_PRINT = 0x0A, /* pop 1 value from the stack and print it */
} OpCode;

#endif