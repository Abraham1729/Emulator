#ifndef tokens_h
#define tokens_h

#define MAX_TOKEN_LEN 32

typedef enum { 
    TOK_LPAREN,     // opening parenthesis
    TOK_RPAREN,     // closing parenthesis
    TOK_SEMI,       // end of statement
    TOK_NUMBER,     // integer literal
    TOK_OPERATOR,   // arithmetic operator
    TOK_EOF         // end of input
} TokenType;


typedef struct {
    TokenType type;
    char text[MAX_TOKEN_LEN];   // e.g. "429" or "+"
    int  value;                 // parsed integer, only meaningful if type == TOK_NUMBER
} Token;


#endif // tokens.H