#include "game.h"

#include <stdio.h>

#define MODEL_MAGIC 0X2E4D444C /* ".MDL" */
#define MODEL_INT_COUNT 5

struct ModelHeader {
    uint32_t magic;
    uint32_t vertices_count;
    uint32_t indices_count;
    uint32_t vertices_offset;
    uint32_t indices_offset;
};

bool game_Model_load(const char *path, struct game_Model *out) {
    FILE *fp = fopen(path, "r");

    if (!fp) {
        printf("File %s could not be opened!\n", path);
        return false;
    }

    struct ModelHeader header;
    fread((void *)&header, sizeof(header) / MODEL_INT_COUNT, MODEL_INT_COUNT, fp);

	if (header.magic != MODEL_MAGIC) {
		printf("Invalid model file!\n");
		fclose(fp);
		return false;
	}
	
	out->vertices_count = header.vertices_count;
	out->indices_count = header.indices_count;
	
	out->vertices = calloc(header.vertices_count, sizeof(float));
	fseek(fp, header.vertices_offset, SEEK_SET);
	fread(out->vertices, sizeof(float), header.vertices_count, fp);
	
	out->indices = calloc(header.indices_count, sizeof(uint32_t));
	fseek(fp, header.indices_offset, SEEK_SET);
	fread(out->vertices, sizeof(uint32_t), header.indices_count, fp);

    fclose(fp);
	return true;
}

static void panic(char *why) {
	fprintf(stderr, "PANIC: %s\n", why);
	exit(EXIT_FAILURE);
}

static GLFWwindow *create_window(u32 width, u32 height, char *title) {	
	GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);	

	if (!window) {
		glfwTerminate();
		panic("Failed to create window!");
	}
	
	glfwMakeContextCurrent(window);
	return window;
}

int game_Game_run(struct game_Game *game, struct game_Options opts) {
	if (!glfwInit())
		return EXIT_FAILURE;

	game->window = create_window(opts.start_width, opts.start_height, opts.title);

	return EXIT_SUCCESS;
}
