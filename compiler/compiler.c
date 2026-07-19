#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "tokentable.h"
#include "charfiles.h"
#include "lexer.h"
#include "parser.h"
#include "codegen.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        exit(1);
    }

    // Get source file //    
    char *source = read_source_file(argv[1]);
    size_t source_len = strlen(source);
    

    // Tokenize source code //
    init_char_table();
    Token tokens[1024];
    int token_count = tokenize(source, source_len, tokens);

    // Validating tokenization //
    printf("Validating Token Stream:\n");
    for (int i = 0; i < token_count; i++) {
        print_token(&tokens[i]);
    } printf("\n");

    // Parse code //
    ASTNode **nodes = malloc(sizeof(ASTNode) * MAX_STATEMENTS);
    if (nodes == NULL) {
        fprintf(stderr, "Failed to allocate ASTNode array in parse_program");
        exit(1);
    }
    int statement_count = parse_program(tokens, nodes);

    // Print results to confirm parsing worked out well //
    printf("Validating ASTNode array:\n");
    for (int i = 0; i < statement_count; i++) {
        print_astnode(nodes[i]);
    } printf("\n");

    // Translate to OPCODES //
    int instruction_count = 0;
    uint8_t *instructions = translate_statements(nodes, statement_count, &instruction_count);
    for (int i = 0; i < instruction_count; i++) {
        printf("Operation %d:\t%d\n", i, instructions[i]);
    }

    free(source);  /* match the malloc — this buffer isn't needed past lexing */
    return 0;
}   