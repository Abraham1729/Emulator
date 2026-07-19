#include "tokens.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

int parse_program(Token* tokens, ASTNode** nodes) {
    // Initialization //
    int position = 0;
    int num_statements = 0;

    while (tokens[position].type != TOK_EOF) {
        nodes[num_statements++] = parse_statement(tokens, &position);
    }

    return num_statements;
}

ASTNode* parse_statement(Token* tokens, int* position) {
    // Expect first token to be an operation, we should error if it isn't //
    Token operation = tokens[(*position)++];

    // Realizing that I need to classify tokens:
    // "Operations" are ADD/SUB/MUL/DIV/PRINT, everything else is invalid
    if (!is_statement_starter(operation)) {
        fprintf(stderr, "Error, parse_statement expected operation token, got %d.\n", operation.type);
        exit(1);
    } else {
        // make AST node //
        ASTNode *node = malloc(sizeof(ASTNode));
        if (node == NULL) {
            fprintf(stderr, "Unable to allocate ASTNode.\n");
            exit(1);
        }
        
        // Make ASTNode children array //
        ASTNode **children = malloc(sizeof(ASTNode*) * MAX_CHILDREN);
        if (children == NULL) {
            fprintf(stderr, "Unable to allocate ASTNode children array.\n");
        }

        // initialize ASTNode //
        node->NodeType = operation.type;
        node->value = operation.value;
        node->num_children = 0;
        node->children = children;

        // Parse args until we hit a semicolon //
        // TODO: This is guarded by EOF token but doesn't gracefully handle it
        while (tokens[*position].type != TOK_SEMI) { // should I include EOF guard?
            node->children[node->num_children++] = parse_argument(tokens, position);
        }
        
        // hit Semi, skip and return node //
        (*position)++;
        return node;
    }
}

ASTNode* parse_argument(Token* tokens, int* position) {
    Token start = tokens[(*position)++];
    if (!(
        start.type == TOK_LPAREN ||
        start.type == TOK_NUMBER
    )) {
        fprintf(stderr, "Error: parse_argument expected number or open paren token, got %d.\n", start.type);
        exit(1);
    } else {
        ASTNode *node = malloc(sizeof(ASTNode));
        if (node == NULL) {
            fprintf(stderr, "Unable to allocate ASTNode.\n");
            exit(1);
        }
        
        // Base case: Number -- no children to process, return node //
        if (start.type == TOK_NUMBER) {
            node->NodeType = start.type;
            node->value = start.value;
            node->num_children = 0;
            // Do I need children ? //
            return node;
            
        } else { // Recursive case: TOK_LPAREN
            // Now need to check to see if it's a legitimate operation, same set as parse_statement //
            Token operation = tokens[(*position)++];
            if (!is_statement_starter(operation)) {
                fprintf(stderr, "Error: parse_argument expected operation token, got %d.\n", operation.type);
                exit(1);
            } else {
                // init children array //
                ASTNode **children = malloc(sizeof(ASTNode*) * MAX_CHILDREN);
                if (children == NULL) {
                    fprintf(stderr, "Unable to allocate ASTNode children array.\n");
                    exit(1);
                }
                
                // Save off the operation info into node //
                node->NodeType = operation.type;
                node->value = operation.value;
                node->num_children = 0;
                node->children = children;

                // Get any arguments for the current operation //
                while(tokens[*position].type != TOK_RPAREN) {
                    node->children[node->num_children++] = parse_argument(tokens, position);
                }

                // Discard RPAREN and return evaluted expression //
                (*position)++;
                return node;
            }
        }
    }
}

int is_statement_starter(Token token) {
    return (
        token.type == TOK_ADD ||
        token.type == TOK_SUB ||
        token.type == TOK_MUL ||
        token.type == TOK_DIV ||
        token.type == TOK_PRINT
    );
}