mkdir -p ./bin
mkdir -p ./apps
gcc -I ./ -I ../emulator/ -I ../programs/ charfiles.c compiler.c lexer.c parser.c tokentable.c codegen.c ../programs/bytefiles.c -o ./bin/compiler
