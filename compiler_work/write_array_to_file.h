#ifndef WRITE_ARRAY_TO_FILE_H
#define WRITE_ARRAY_TO_FILE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "tokens.h"

static inline const char *path_basename(const char *path) {
    const char *base = strrchr(path, '/');
    if (base) {
        return base + 1;
    }
    base = strrchr(path, '\\');
    return base ? base + 1 : path;
}

static inline void ensure_output_dir(void) {
    if (mkdir("output", 0755) != 0 && errno != EEXIST) {
        fprintf(stderr, "could not create output directory: %s\n", strerror(errno));
        exit(1);
    }
}

static inline char *build_output_path(const char *input_path) {
    const char *base = path_basename(input_path);
    size_t len = strlen("output/") + strlen(base) + 1;
    char *output_path = malloc(len);
    if (output_path == NULL) {
        fprintf(stderr, "out of memory allocating output path\n");
        exit(1);
    }
    snprintf(output_path, len, "output/%s", base);
    return output_path;
}

static inline void write_token_line(FILE *fp, const Token *token) {
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

static inline void write_array_to_file(const char *path, const Token *tokens, int token_count) {
    ensure_output_dir();

    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        fprintf(stderr, "could not open output file: %s\n", path);
        exit(1);
    }

    for (int i = 0; i < token_count; i++) {
        write_token_line(fp, &tokens[i]);
    }

    fclose(fp);
}


#endif // WRITE_ARRAY_TO_FILE_H
