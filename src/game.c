#include "game.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

#define MODEL_MAGIC 0x4C444D2E
#define MODEL_INT_COUNT 5

static void panic(char *why) {
	fprintf(stderr, "PANIC: %s\n", why);
	exit(EXIT_FAILURE);
}

struct ModelHeader {
    u32 magic;
    u32 vertices_count;
    u32 indices_count;
    u32 vertices_offset;
    u32 indices_offset;
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
		printf("Magic: %x\n", header.magic);
		printf("Invalid model file!\n");
		fclose(fp);
		return false;
	}
	
	out->vertices_count = header.vertices_count;
	out->indices_count = header.indices_count;
	
	/* I think the bytes are not actually being copied */

	printf("vertices_offset: %d\n", header.vertices_offset);
	out->vertices = calloc(header.vertices_count, sizeof(float));
	
	fseek(fp, header.vertices_offset, SEEK_SET);
	fread(out->vertices, sizeof(f32), header.vertices_count, fp);
	
	out->indices = calloc(header.indices_count, sizeof(u32));
	fseek(fp, header.indices_offset, SEEK_SET);
	fread(out->indices, sizeof(u32), header.indices_count, fp);
	
    fclose(fp);
	return true;
}

void game_Model_kill(struct game_Model *model) {
	free(model->vertices);
	free(model->indices);
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

static void cleanup_game(struct game_Game *game) {
	glfwTerminate();
}

static void debug_render() {
	/* TODO */
}

int game_Game_run(struct game_Game *game, struct game_Options opts) {
	if (!glfwInit())
		return EXIT_FAILURE;

	game->window = create_window(opts.start_width, opts.start_height, opts.title);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(game->window)) {
		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		debug_render();
		glfwSwapBuffers(game->window);
		glfwPollEvents();
	}

	cleanup_game(game);

	return EXIT_SUCCESS;
}
