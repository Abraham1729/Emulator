#ifndef tokens_h
#define tokens_h

#define MAX_TOKEN_LEN 32

typedef enum { 
    TOK_UNKNOWN,    // unrecognized character
    TOK_LPAREN,     // opening parenthesis
    TOK_RPAREN,     // closing parenthesis
    TOK_SEMI,       // end of statement
    TOK_NUMBER,     // integer literal
    TOK_ADD,        // addition operator
    TOK_SUB,        // subtraction operator
    TOK_MUL,        // multiplication operator
    TOK_DIV,        // division operator
    TOK_PRINT,      // print statement
    TOK_HALT,       // halt statement,
    TOK_COMMENT,    // comment
    TOK_EOF         // end of input
} TokenType;


typedef struct {
    TokenType type;
    char text[MAX_TOKEN_LEN];   // e.g. "429" or "+"
    int  value;                 // parsed integer, only meaningful if type == TOK_NUMBER
} Token;

void print_token(const Token *token) {
    switch (token->type) {
        case TOK_UNKNOWN: printf("UNKNOWN (%s)\n", token->text); break;
        case TOK_LPAREN:  printf("LPAREN\n"); break;
        case TOK_RPAREN:  printf("RPAREN\n"); break;
        case TOK_SEMI:    printf("SEMI\n"); break;
        case TOK_NUMBER:  printf("NUMBER, Value: %d\n", token->value); break;
        case TOK_ADD:     printf("ADD\n"); break;
        case TOK_SUB:     printf("SUB\n"); break;
        case TOK_MUL:     printf("MUL\n"); break;
        case TOK_DIV:     printf("DIV\n"); break;
        case TOK_PRINT:   printf("PRINT\n"); break;
        case TOK_HALT:    printf("HALT\n"); break;
        case TOK_EOF:     printf("EOF\n"); break;
        case TOK_COMMENT: printf("COMMENT (%s)\n", token->text); break;
    }
}


#endif // tokens.H