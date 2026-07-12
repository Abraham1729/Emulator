#ifndef BYTEFILES_H
#define BYTEFILES_H

void write_bytes_to_file(const char *path, const uint8_t *bytes, size_t length);
uint8_t *read_bytecode_file(const char *path, size_t *out_length);

#endif // BYTEFILES_H