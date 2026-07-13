mkdir -p ./bin
gcc -I ./ charfiles.c compiler.c lexer.c tokentable.c -o ./bin/compiler
