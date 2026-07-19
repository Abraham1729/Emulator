# Emulator

This project features a stack-based virtual machine and a compiler for a custom language.
The compiler is still a work in progress, currently only featuring a lexer to tokenize the language --
a parser is still needed before the src code can be translated into a custom assembly language.

The virtual machine is ready to act as an emulator for my custom assembly language.
There are currently 4 programs written in the custom assembly language which can be passed to this emulator for execution.
The compiler and emulator are written in C. This should give my custom language / instruction set the ability to run independent of the specific hardware I choose today vs tomorrow.

The long term goal would be to mature my language enough for it to be able to compile itself.

https://excalidraw.com/#json=_ka2NVSzjxXA169Nk0wRC,NFQzJKBGmqazE-21fWa7cA

![End to end flow from src file to execution](end-to-end.png "End to End Flow")


## Project structure

- `emulator/` — the virtual machine
  - `vm.c` / `vm.h` — fetch-decode-execute loop, stack, program counter
  - `opcodes.h` — the instruction set
- `compiler/` — lexer for source code (parser in progress)
  - `compiler.c` — driver: reads source, tokenizes, prints the token stream
  - `tokens.h` — token types and the `Token` struct
  - `tokentable.h` — dispatch table mapping single characters to token types
  - `charfiles.c/.h` — reads a source file into memory
  - `src/program.txt` — example source file
- `programs/` — bytecode file I/O and demo programs
  - `bytefiles.c/.h` — raw binary read/write (`fwrite`/`fread`, no text
    encoding — bytecode is treated as opaque bytes, not a C string, since
    `0x00` is a legitimate opcode value)
  - `write_program.c` — writes four hardcoded demo programs out as binaries
  - `run_program.c` — loads an arbitrary binary file and runs it on the VM
  - `hardcoded/*.h` — the four demo programs as raw opcode arrays
    (`arithmetic`, `jump_demo`, `loop_countdown`, `stack_ops`)

## Building and running

Each subproject has its own build/run scripts:

**Compiler (lexer only, for now):**
```sh
cd compiler
./scripts/run.sh
```
Builds the compiler, runs it against `src/program.txt`, and prints the
resulting token stream.

**VM + demo programs:**
```sh
cd programs
./scripts/run.sh
```
Writes the four demo programs to `.bin` files under `apps/`, then loads and
runs each one through the VM.