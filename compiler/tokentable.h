#ifndef tokentable_h
#define tokentable_h
#include <tokens.h>

extern TokenType char_table[256];  /* maps ASCII characters to token types */
void init_char_table(void); // Does the mapping //

#endif // tokentable_h