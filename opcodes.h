#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

/* Operation codes for the virtual machine */
typedef enum {
    OP_HALT  = 0x00, /* halt execution */
    OP_PUSH  = 0x01, /* push 1-byte-literal onto the stack */
    OP_PRINT = 0x02, /* pop 1 value from the stack and print it */
    OP_ADD   = 0x03, /* pop 2 values from the stack, add them, and push the result */
    OP_SUB   = 0x04, /* pop 2 values from the stack, subtract the second from the first, and push the result */
    OP_MUL   = 0x05, /* pop 2 values from the stack, multiply them, and push the result */
    OP_DIV   = 0x06, /* pop 2 values from the stack, divide the second by the first, and push the result */
} OpCode;

#endif