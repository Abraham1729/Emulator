#ifndef tokentable_h
#define tokentable_h
#include "tokens.h"

TokenType char_table[256];  /* maps ASCII characters to token types */

void init_char_table(void) {
    for (int i = 0; i < 256; i++) char_table[i] = TOK_UNKNOWN;  /* default to unknown character */
    char_table['('] = TOK_LPAREN;
    char_table[')'] = TOK_RPAREN;
    char_table[';'] = TOK_SEMI;
    char_table['+'] = TOK_ADD;
    char_table['-'] = TOK_SUB;
    char_table['*'] = TOK_MUL;
    char_table['/'] = TOK_DIV;
    char_table['#'] = TOK_COMMENT;
    // digits & whitepsace are handled specially in the lexer, so we don't need to map them here
}

#endif // tokentable_h