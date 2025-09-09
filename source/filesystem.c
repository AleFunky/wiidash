#include <fat.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>

#include "filesystem.h"
#include "game.h"

char *read_file(const char *filepath, size_t *out_size) {
    FILE *f = fopen(filepath, "rb");
    if (!f) {
        output_log("Failed to open file: %s\n", filepath);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        output_log("Failed to allocate buffer\n");
        fclose(f);
        return NULL;
    }
    fread(buffer, 1, size, f);
    buffer[size] = '\0'; // Null-terminate for text files
    fclose(f);

    if (out_size) *out_size = size;
    return buffer;
}