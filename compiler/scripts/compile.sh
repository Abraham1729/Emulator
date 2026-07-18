mkdir -p ./bin
gcc -I ./ charfiles.c compiler.c lexer.c parser.c tokentable.c -o ./bin/compiler
