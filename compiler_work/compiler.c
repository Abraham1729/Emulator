#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "tokentable.h"

/* Reads the entire contents of a source file into a heap-allocated,
 * null-terminated buffer. Caller is responsible for free()-ing the
 * returned pointer when done with it.
 */
char *read_source_file(const char *path) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        fprintf(stderr, "could not open source file: %s\n", path);
        exit(1);
    }

    /* Find the file's size: seek to the end, ask "where am I?",
     * then seek back to the start so reading begins from byte 0. */
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    /* +1 so there's room for a null terminator after the real content —
     * fread() itself does NOT null-terminate anything for us. */
    char *buffer = malloc(size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "out of memory reading %s\n", path);
        fclose(fp);
        exit(1);
    }

    size_t bytes_read = fread(buffer, 1, size, fp);
    buffer[bytes_read] = '\0';  /* now safe to treat buffer as a C string */

    fclose(fp);
    return buffer;
}

int main(void) {
    char *source = read_source_file("/home/abraham/Projects/Emulator/compiler_work/example.txt");

    // printf("read %zu bytes:\n%s\n", strlen(source), source);

    // Need to iterate over each char in the src
    // First check if whitespace or numerical
    // If whitespace, skip
    // If numerical, parse the number and create a token for it
    // If operator, create a token for it
    init_char_table();

    for (int i = 0; i < strlen(source); i++) {
        char c = source[i];
        if (isspace(c)) {
            continue;  // skip whitespace
        } else if (isdigit(c)) {
            // parse number
            int start = i;
            while (i < strlen(source) && isdigit(source[i])) {
                i++;
            }
            int length = i - start;
            char number_str[MAX_TOKEN_LEN];
            strncpy(number_str, &source[start], length);
            number_str[length] = '\0';
            printf("Token: NUMBER, Value: %s\n", number_str);
            i--;  // adjust for the outer loop increment
        } else {
            TokenType token_type = char_table[(unsigned char)c];
            print_token(&(Token){.type = token_type, .text = {c}, .value = 0});
        }
    }

    free(source);  /* match the malloc — this buffer isn't needed past lexing */
    return 0;
}