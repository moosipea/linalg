#include "game.h"
#include "shader.h"

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

static void cleanup_game(struct game_Game *game) {
    (void) game;
	glfwTerminate();
}

static void glfw_error_callback(i32 error, const char *desc) {
    fprintf(stderr, "[GLFW ERROR] (%d): %s", error, desc);
}

static void glfw_key_callback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mods) {
    (void) scancode;
    (void) mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int game_Game_run(struct game_Game *game, struct game_Options opts) {
	if (!glfwInit())
		PANIC("Failed to initialize GLFW");

    glfwSetErrorCallback(glfw_error_callback);
    game->window = create_window(opts.start_width, opts.start_height, opts.title);
    glfwSetKeyCallback(game->window, glfw_key_callback);
    
	/* Initialize OpenGL */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
		PANIC("Failed to initialize GLAD");

    glfwSwapInterval(1);

    /* Load shader program */ 
    char *vertex_src = game_load_string("res/vertex.glsl");
    char *fragment_src = game_load_string("res/fragment.glsl");
    u32 program = game_Program_load(vertex_src, fragment_src);
    free(vertex_src);
    free(fragment_src);

    f32 vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    u32 indices[] = {  
        0, 1, 3,
        1, 2, 3
    };  

	u32 vbo, ebo, vao;
	glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    i32 width, height;
    while (!glfwWindowShouldClose(game->window)) {
        glfwGetFramebufferSize(game->window, &width, &height);
		glViewport(0, 0, width, height);
        glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Test rendering */
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(game->window);
        glfwPollEvents();
    }

    cleanup_game(game);

    return EXIT_SUCCESS;
}
