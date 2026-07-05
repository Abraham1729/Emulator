#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"
#include "vm.h"

void vm_init(VM *vm, const uint8_t *program, size_t program_size) {
    if (program_size > MEM_SIZE) {
        fprintf(stderr, "Program size exceeds memory size\n");
        exit(EXIT_FAILURE);
    }
    memcpy(vm->memory, program, program_size);
    vm->sp = 0;
    vm->pc = 0;
    vm->running = 1;
}

static void push(VM *vm, int32_t value) {
    if (vm->sp >= STACK_SIZE) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    vm->stack[vm->sp++] = value;
}

static int32_t pop(VM *vm) {
    if (vm->sp == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return vm->stack[--vm->sp];
}

void vm_run(VM *vm) {
    while (vm->running) {
        uint8_t opcode = vm->memory[vm->pc++];
        switch (opcode) {
            case OP_HALT:
                vm->running = 0;
                break;

            case OP_PUSH: {
                uint8_t value = vm->memory[vm->pc++];
                push(vm, value);
                break;
            }

            case OP_DROP: {
                (void)pop(vm);
                break;
            }

            case OP_DUP: {
                int32_t value = pop(vm);
                push(vm, value);
                push(vm, value);
                break;
            }

            case OP_SWAP: {
                int32_t b = pop(vm);
                int32_t a = pop(vm);
                push(vm, b);
                push(vm, a);
                break;
            }

            case OP_OVER: {
                int32_t b = pop(vm);
                int32_t a = pop(vm);
                push(vm, a);
                push(vm, b);
                push(vm, a);
                break;
            }

            case OP_PRINT: {
                int32_t value = pop(vm);
                printf("%d\n", value);
                break;
            }

            case OP_JUMP: {
                uint16_t target = vm->memory[vm->pc++];
                if (target >= MEM_SIZE) {
                    fprintf(stderr, "Jump target out of bounds\n");
                    exit(EXIT_FAILURE);
                }
                vm->pc = (uint8_t)target;
                break;
            }

            case OP_JMPZ: {
                uint16_t target = vm->memory[vm->pc++];
                if (target >= MEM_SIZE) {
                    fprintf(stderr, "Jump target out of bounds\n");
                    exit(EXIT_FAILURE);
                }
                int32_t value = pop(vm);
                if (value == 0) {
                    vm->pc = (uint8_t)target;
                }
                break;
            }

            case OP_ADD: {
                int32_t b = pop(vm);
                int32_t a = pop(vm);
                push(vm, a + b);
                break;
            }
            case OP_SUB: {
                int32_t b = pop(vm);
                int32_t a = pop(vm);
                push(vm, a - b);
                break;
            }
            case OP_MUL: {
                int32_t b = pop(vm);
                int32_t a = pop(vm);
                push(vm, a * b);
                break;
            }
            case OP_DIV: {
                int32_t b = pop(vm);
                int32_t a = pop(vm);
                if (b == 0) {
                    fprintf(stderr, "Division by zero\n");
                    exit(EXIT_FAILURE);
                }
                push(vm, a / b);
                break;
            }
            default:
                fprintf(stderr, "Unknown opcode: 0x%02X\n", opcode);
                exit(EXIT_FAILURE);
        }
    }
}

