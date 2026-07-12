#ifndef WRITE_BIN_ARRAY_TO_FILE_H
#define WRITE_BIN_ARRAY_TO_FILE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "tokens.h"

static inline void write_bin_token_line(FILE *fp, const Token *token) {
    const char *name = token_type_name(token->type);
    switch (token->type) {
        case TOK_NUMBER:
            fprintf(fp, "%d\n", token->value);
            break;
        case TOK_UNKNOWN:
        case TOK_COMMENT:
            fprintf(fp, "%s %s\n", name, token->text);
            break;
        default:
            fprintf(fp, "%s\n", name);
            break;
    }
}

static inline void write_bin_array_to_file(const char *path, const Token *tokens, int token_count) {
    ensure_output_dir();

    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        fprintf(stderr, "could not open output file: %s\n", path);
        exit(1);
    }

    for (int i = 0; i < token_count; i++) {
        write_bin_token_line(fp, &tokens[i]);
    }

    fclose(fp);
}

#endif // WRITE_ARRAY_TO_FILE_H
