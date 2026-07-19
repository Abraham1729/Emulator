#ifndef PARSER_H
#define PARSER_H
#include "tokens.h"

#define MAX_CHILDREN 2
#define MAX_STATEMENTS 32

// Node structure to contain a statement //
typedef struct ASTNode ASTNode;

struct ASTNode {
    TokenType NodeType;
    int value;
    int num_children;
    struct ASTNode **children;
};


// Takes in an array of tokens,
// Builds array of ASTNodes by calling parse_statement until EOF
int parse_program(Token* tokens, ASTNode** nodes);

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

static void print_indent(int count) {
    for (int i = 0; i < count; i++) {
        printf("\t");
    }
}

// Printer for ASTNode Type to confirm parser works as intended //
static void print_astnode_helper(const ASTNode *node, int indent_count) {
    
    if (node->NodeType == TOK_NUMBER) {
        print_indent(indent_count);
        printf("%d\n", node->value);
    } else {
        print_indent(indent_count);
        printf("%s\n", token_type_name(node->NodeType));

        for (int i = 0; i < node->num_children; i++) {
            print_astnode_helper(node->children[i], indent_count + 1);
        }
    }
    
}

static void print_astnode(const ASTNode *node) {
    print_astnode_helper(node, 0);
}


#endif // PARSER_H