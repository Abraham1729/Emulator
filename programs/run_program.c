#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "bytefiles.h"

// I want to update this to take an arbitrary .bin file as input, read it into a uint8_t array, and then run the VM on that array. This will allow me to test the VM with different programs without having to recompile the emulator each time.
int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program.bin>\n", argv[0]);
        exit(1);
    }

// Convert raw string into array of uint8_t instructions //
    size_t program_size = 1024;
    uint8_t *program = read_bytecode_file(argv[1], &program_size);

    VM vm;
    vm_init(&vm, program, program_size);
    vm_run(&vm);

    return 0;
}
