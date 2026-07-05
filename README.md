# Emulator

A small stack-based virtual machine written in C.

## Project structure
- `emulator/` - VM core implementation and headers
  - `emulator/vm.c` - VM execution loop and stack operations
  - `emulator/vm.h` - VM structure and public API
  - `emulator/opcodes.h` - opcode definitions
- `programs/` - example programs that load bytecode into the VM
  - `programs/arithmetic.c` - arithmetic demo
  - `programs/stack_ops.c` - stack operation demo
- `Makefile` - builds the demo executables into `bin/`
- `bin/` - compiled demo binaries

## Build
```sh
make all
```

## Run
```sh
./bin/arithmetic
./bin/stack_ops
```

## Clean
```sh
make clean
```
