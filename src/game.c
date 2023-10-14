#include "game.h"

#include <stdio.h>
#include <string.h>

#define MODEL_MAGIC 0x4C444D2E
#define MODEL_INT_COUNT 5

bool game_Model_load(const char *path, struct game_Model *out) {
	struct ModelHeader {
    	u32 magic;
    	u32 vertices_count;
    	u32 indices_count;
    	u32 vertices_offset;
    	u32 indices_offset;
	} header;

    FILE *fp = fopen(path, "r");

    if (!fp) {
        printf("File %s could not be opened!\n", path);
        return false;
    }

    fread((void *)&header, sizeof(header) / MODEL_INT_COUNT, MODEL_INT_COUNT, fp);

    if (header.magic != MODEL_MAGIC) {
        printf("Magic: %x\n", header.magic);
        printf("Invalid model file!\n");
        fclose(fp);
        return false;
    }

    out->vertices_count = header.vertices_count;
    out->indices_count = header.indices_count;

    out->vertices = calloc(header.vertices_count, sizeof(f32));
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window) {
        glfwTerminate();
        PANIC("Failed to create window!");
    }

    glfwMakeContextCurrent(window);
    return window;
}

static void cleanup_game(struct game_Game *_game) {
	glfwTerminate();
}

static void debug_render(void) {
	
}

int game_Game_run(struct game_Game *game, struct game_Options opts) {
	if (!glfwInit())
		PANIC("Failed to initialize GLFW");

    game->window = create_window(opts.start_width, opts.start_height, opts.title);
	
	/* Initialize OpenGL */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
		PANIC("Failed to initialize GLAD");

    glfwSwapInterval(1);

	/* OpenGL begin */
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	u32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* OpenGL end */

    while (!glfwWindowShouldClose(game->window)) {
		glViewport(0, 0, opts.start_width, opts.start_height);
        glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        debug_render();
        glfwSwapBuffers(game->window);
        glfwPollEvents();
    }

    cleanup_game(game);

    return EXIT_SUCCESS;
}
