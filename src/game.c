#include "game.h"

#include <stdio.h>

#define MODEL_MAGIC 0X2E4D444C /* ".MDL" */

struct ModelHeader {
    int magic;
    int vertices_count;
    int indices_count;
    int vertices_offset;
    int indices_offset;
};

void game_Model_load(const char *path) {
    FILE *fp = fopen(path, "r");

    if (!fp) {
        printf("File %s could not be opened!\n", path);
        return;
    }

    struct ModelHeader header;
    fread((void *)&header, sizeof(header) / 5, 5, fp);

    printf("magic = %s\n", (char *)&header.magic);
    printf("vertices_count = %d\n", header.vertices_count);
    printf("indices_count = %d\n", header.indices_count);
    printf("vertices_offset = %d\n", header.vertices_offset);
    printf("indices_offset = %d\n", header.indices_offset);

    fclose(fp);
}
