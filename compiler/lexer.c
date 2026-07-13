#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "tokentable.h"

int tokenize(const char *source, size_t source_len, Token *tokens) {
    int token_count = 0;
    for (size_t i = 0; i < source_len; i++) {
        char c = source[i];

        // Skip whitespace characters
        if (isspace((unsigned char)c)) {
            continue;
        }
        
        // Parse potentially multi-digit numbers
        else if (isdigit((unsigned char)c)) {
            size_t start = i;
            while (i < source_len && isdigit((unsigned char)source[i])) {
                i++;
            }
            size_t length = i - start;
            char number_str[MAX_TOKEN_LEN];

            // Bad behavior on excessively sized numerical tokens, need to come up with a better plan
            if (length >= MAX_TOKEN_LEN) {
                length = MAX_TOKEN_LEN - 1;
            }
            memcpy(number_str, &source[start], length);
            number_str[length] = '\0';

            Token token = {0};
            token.type = TOK_NUMBER;
            token.value = atoi(number_str);
            strncpy(token.text, number_str, MAX_TOKEN_LEN - 1);
            token.text[MAX_TOKEN_LEN - 1] = '\0';
            tokens[token_count++] = token;

            i--;
        }
        
        // Match remaining single-character tokens using the char_table
        else {
            TokenType token_type = char_table[(unsigned char)c];

            // if it's a comment, skip the rest of the line //
            if (token_type == TOK_COMMENT) {
                while (i < source_len && source[i] != '\n') {
                    i++;
                }
                continue; // no comment token
            }

            // All other tokens we want to save into the token array //
            Token token = {0};
            token.type = token_type;
            token.value = 0;
            token.text[0] = c;
            token.text[1] = '\0';
            tokens[token_count++] = token;
        }
    }
    return token_count;
}