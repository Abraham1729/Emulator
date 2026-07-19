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
        printf("parse_statement: position %d operation type %d.\n", *position - 1, node->NodeType);

        // Parse args until we hit a semicolon //
        while (tokens[*position].type != TOK_SEMI) { // should I include EOF guard?
            node->children[node->num_children++] = parse_argument(tokens, position);
            printf("Finished parsing arg\n");
        }
        
        // hit Semi, return node //
        return node;
    }
}

ASTNode* parse_argument(Token* tokens, int* position) {
    Token current = tokens[(*position)++];
    if (!(
        current.type == TOK_LPAREN ||
        current.type == TOK_NUMBER
    )) {
        fprintf(stderr, "Error: parse_argument expected number or open paren token, got %d.\n", current.type);
        exit(1);
    } else {
        printf("Parsing on position %d token type %d\n", *position - 1, (int)(current.type));
        ASTNode *node = malloc(sizeof(ASTNode));
        if (node == NULL) {
            fprintf(stderr, "Unable to allocate ASTNode.\n");
            exit(1);
        }
        node->num_children = 0;
        node->value = current.value;

        // printf("successful assignment of base values to node\n");
        
        // Base case: Number -- no children to process, return node //
        if (current.type == TOK_NUMBER) {
            printf("Base case: Number\n");
            node->NodeType = current.type;
            printf("wrote to node\n");
            // Do I need to 0-initialize my children ? //
            return node;
            
        } else { // Recursive case: TOK_LPAREN
            // Now need to check to see if it's a legitimate operation, same set as parse_statement //
            printf("Recursive case: Lparen\n");
            current = tokens[(*position)++];
            if (!is_statement_starter(current)) {
                fprintf(stderr, "Error: parse_argument expected operation token, got %d.\n", current.type);
                exit(1);
            } else {
                // Save off the operation info into node //
                node->NodeType = current.type;

                // Get any arguments for the current operation //
                while(tokens[*position].type != TOK_RPAREN) {
                    node->children[node->num_children++] = parse_argument(tokens, position);
                }

                // At this point, we've pulled all children / args for this operation node //
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