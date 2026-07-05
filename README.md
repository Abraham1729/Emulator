# Emulator

A small stack-based virtual machine written in C.

## Project structure
- `emulator/` - VM core implementation and headers
  - `emulator/vm.c` - VM execution loop, stack operations, and control-flow support
  - `emulator/vm.h` - VM structure and public API
  - `emulator/opcodes.h` - opcode definitions
- `programs/` - example programs that load bytecode into the VM
  - These program files in C are simply constructing an instruction sequence in memory to pass to the emulator, rather than having those instructions written out as a bytefile on disk. This is purely a conveinence of legibility for the author and shouldn't meaningfully detract from the spirit of trying to write basic programs in a custom instruction set.
  - `programs/arithmetic.c` - arithmetic demo
  - `programs/stack_ops.c` - stack operation demo
  - `programs/loop_countdown.c` - countdown loop using `JMPZ`
  - `programs/jump_demo.c` - jump demonstration
- `Makefile` - builds every demo program in `programs/` into matching binaries in `bin/`
- `bin/` - compiled demo binaries
- `.gitignore` - ignores build outputs in `bin/` and object files under `emulator/`

## Build
```sh
make all
```

## Run
```sh
./bin/arithmetic
./bin/stack_ops
./bin/loop_countdown
./bin/jump_demo
```

## Clean
```sh
make clean
```
