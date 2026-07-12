#ifndef read_source_file_h
#define read_source_file_h

#include <stdio.h>
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

#endif // read_source_file_h