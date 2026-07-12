#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "tokentable.h"
#include "charfiles.h"
#include "write_array_to_file.h"
#include "write_bin_array_to_file.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        exit(1);
    }

    char *source = read_source_file(argv[1]);

    init_char_table();

    Token tokens[1024];
    int token_count = 0;

    size_t source_len = strlen(source);
    for (size_t i = 0; i < source_len; i++) {
        char c = source[i];

        // Skip whitespace characters //
        if (isspace((unsigned char)c)) {
            continue;
        }
        
        // Parse potentially multi-digit numbers //
        else if (isdigit((unsigned char)c)) {
            size_t start = i;
            while (i < source_len && isdigit((unsigned char)source[i])) {
                i++;
            }
            size_t length = i - start;
            char number_str[MAX_TOKEN_LEN];

            // Bad behavior on excedssively sized numerical tokens, need to come up with a better plan //
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
        
        // Match remaining single-character tokens using the char_table //
        else {
            TokenType token_type = char_table[(unsigned char)c];

            // If it's a comment, skip the rest of the line //
            if (token_type == TOK_COMMENT) {
                while (i < source_len && source[i] != '\n') {
                    i++;
                }
                continue;  // skip adding a token for the comment itself
            }

            // All other tokens we want to save in the token array //
            Token token = {0};
            token.type = token_type;
            token.value = 0;
            token.text[0] = c;
            token.text[1] = '\0';
            tokens[token_count++] = token;
        }
    }

    // Print our array of tokens to validate that the lexer is working correctly //
    for (int j = 0; j < token_count; j++) {
        print_token(&tokens[j]);
    }

    char *output_path = build_output_path(argv[1]);
    write_bin_array_to_file(output_path, tokens, token_count);
    free(output_path);

    free(source);  /* match the malloc — this buffer isn't needed past lexing */
    return 0;
}   