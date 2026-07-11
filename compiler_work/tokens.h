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
    TOK_HALT,       // halt statement
    TOK_EOF         // end of input
} TokenType;


typedef struct {
    TokenType type;
    char text[MAX_TOKEN_LEN];   // e.g. "429" or "+"
    int  value;                 // parsed integer, only meaningful if type == TOK_NUMBER
} Token;

void print_token(const Token *token) {
    switch (token->type) {
        case TOK_UNKNOWN: printf("Token: UNKNOWN (%s)\n", token->text); break;
        case TOK_LPAREN:  printf("Token: LPAREN\n"); break;
        case TOK_RPAREN:  printf("Token: RPAREN\n"); break;
        case TOK_SEMI:    printf("Token: SEMI\n"); break;
        case TOK_NUMBER:  printf("Token: NUMBER, Value: %d\n", token->value); break;
        case TOK_ADD:     printf("Token: ADD\n"); break;
        case TOK_SUB:     printf("Token: SUB\n"); break;
        case TOK_MUL:     printf("Token: MUL\n"); break;
        case TOK_DIV:     printf("Token: DIV\n"); break;
        case TOK_PRINT:   printf("Token: PRINT\n"); break;
        case TOK_HALT:    printf("Token: HALT\n"); break;
        case TOK_EOF:     printf("Token: EOF\n"); break;
    }
}


#endif // tokens.H