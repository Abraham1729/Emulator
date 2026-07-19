mkdir -p ./bin
gcc -I ./ -I ../emulator/ charfiles.c compiler.c lexer.c parser.c tokentable.c codegen.c -o ./bin/compiler
