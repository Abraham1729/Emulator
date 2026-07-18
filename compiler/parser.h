#ifndef PARSER_H
#define PARSER_H
#include "tokens.h"

#define MAX_CHILDREN 2
#define MAX_STATEMENTS 32

// Node structure to contain a statement //
typedef struct ASTNode {
    TokenType NodeType;
    int value;
    int num_children;
    ASTNode children[MAX_CHILDREN];
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

// helper func for parse_arg & parse_statement
// returns 1 if legitimate statement-starting token
// returns 0 otherwise
int is_statement_starter(Token token);

#endif // PARSER_H