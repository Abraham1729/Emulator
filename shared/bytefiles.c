#include <stdio.h>

void write_bytes_to_file(const char *path, const uint8_t *bytes, size_t length) {
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        fprintf(stderr, "could not open output file: %s\n", path);
        exit(1);
    }

    size_t bytes_written = fwrite(bytes, 1, length, fp);
    if (bytes_written != length) {
        fprintf(stderr, "error writing to output file: %s\n", path);
        fclose(fp);
        exit(1);
    }

    fclose(fp);
}

uint8_t *read_bytecode_file(const char *path, size_t *out_length) {
    FILE *fp = fopen(path, "rb");   /* "rb" — binary mode, no text translation */
    if (fp == NULL) {
        fprintf(stderr, "could not open bytecode file: %s\n", path);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);          /* true byte count, from the OS, not from content */
    fseek(fp, 0, SEEK_SET);

    uint8_t *buffer = malloc(size); /* no +1 — there's no terminator to make room for */
    if (buffer == NULL) {
        fprintf(stderr, "out of memory reading %s\n", path);
        fclose(fp);
        exit(1);
    }

    size_t bytes_read = fread(buffer, 1, size, fp);
    if (bytes_read != (size_t)size) {
        fprintf(stderr, "short read on %s (%zu of %ld bytes)\n", path, bytes_read, size);
        exit(1);
    }

    fclose(fp);
    *out_length = bytes_read;
    return buffer;
}
