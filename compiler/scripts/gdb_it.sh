mkdir -p ./bin
gcc -I ./ charfiles.c compiler.c lexer.c parser.c tokentable.c -o ./bin/compiler_debug -g
gdb --args ./bin/compiler_debug ./src/parser_test.txt