#ifndef VM_H
#define VM_H

#include <stddef.h>
#include <stdint.h>

/* Virtual machine structure */
#define MEM_SIZE    256
#define STACK_SIZE  32

typedef struct {
    uint8_t memory[MEM_SIZE];  /* memory for instructions and data */
    int32_t stack[STACK_SIZE]; /* stack for operands */
    uint8_t sp;                /* stack pointer */
    uint8_t pc;                /* program counter */
    uint8_t running;           /* flag to indicate if the VM is running */
} VM;

void vm_init(VM *vm, const uint8_t *program, size_t program_size);
void vm_run(VM *vm);

#endif


