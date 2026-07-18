#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "tokentable.h"
#include "charfiles.h"
#include "lexer.h"
#include "parser.h"


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

    // Print our array of tokens to validate that the lexer is working correctly //
    for (int j = 0; j < token_count; j++) {
        print_token(&tokens[j]);
    }

    // Parse code //
    ASTNode **nodes = malloc(sizeof(ASTNode) * MAX_STATEMENTS);
    if (nodes == NULL) {
        fprintf(stderr, "Failed to allocate ASTNode array in parse_program");
        exit(1);
    }
    printf("Parsing tokens\n");
    int statement_count = parse_program(tokens, nodes);

    // Print results to confirm parsing worked out well //
    printf("Validating ASTNode array:\n");
    for (int i = 0; i < statement_count; i++) {
        print_astnode(nodes[i]);
    }

    free(source);  /* match the malloc — this buffer isn't needed past lexing */
    return 0;
}   