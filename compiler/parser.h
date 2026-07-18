#ifndef PARSER_H
#define PARSER_H
#include "tokens.h"

// Node structure to contain a statement //
typedef struct ASTNode {
    TokenType NodeType;
    int value;
    int num_children;
    ASTNode **children;
} ASTNode;


// Takes in an array of tokens,
// Builds array of ASTNodes by calling parse_statement until EOF
ASTNode** parse_program(Token* tokens);

// Takes tokens & pointer to current position in token array
// Reads op, parses args, ends at semicolon
ASTNode* parse_statement(Token* tokens, int* position);

// Takes tokens & pointer to current position in token array, 
// Recursive case: Handles LP -> RP
// Base case: Just handles a raw number
ASTNode* parse_argument(Token* tokens, int* position);

#endif // PARSER_H