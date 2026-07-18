#ifndef tokens_h
#define tokens_h
#include <stdio.h>

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
    TOK_EOF,        // EOF
} TokenType;


typedef struct {
    TokenType type;
    char text[MAX_TOKEN_LEN];   // e.g. "429" or "+"
    int  value;                 // parsed integer, only meaningful if type == TOK_NUMBER
} Token;

static inline const char *token_type_name(TokenType type) {
    static const char *names[] = {
        [TOK_UNKNOWN] = "UNKNOWN",
        [TOK_LPAREN]  = "LPAREN",
        [TOK_RPAREN]  = "RPAREN",
        [TOK_SEMI]    = "SEMI",
        [TOK_NUMBER]  = "NUMBER",
        [TOK_ADD]     = "ADD",
        [TOK_SUB]     = "SUB",
        [TOK_MUL]     = "MUL",
        [TOK_DIV]     = "DIV",
        [TOK_PRINT]   = "PRINT",
        [TOK_HALT]    = "HALT",
        [TOK_COMMENT] = "COMMENT",
        [TOK_EOF]     = "EOF",
    };

    if (type < 0 || type > TOK_COMMENT) {
        return "UNKNOWN";
    }
    return names[type];
}

static void print_token(const Token *token) {
    const char *name = token_type_name(token->type);
    switch (token->type) {
        case TOK_UNKNOWN:
            printf("%s (%s)\n", name, token->text);
            break;
        case TOK_NUMBER:
            printf("%d\n", token->value);
            break;
        case TOK_COMMENT:
            printf("%s (%s)\n", name, token->text);
            break;
        default:
            printf("%s\n", name);
            break;
    }
}


#endif // tokens.H