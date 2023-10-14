#include "shader.h"
#include <stdio.h>

static u32 create_shader(const char *src, u32 kind) {
    u32 shader = glCreateShader(kind);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    i32 success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        if (kind == GL_VERTEX_SHADER) {
            PANIC("Vertex compilation failed: %s", info_log);
        } else {
            PANIC("Fragment compilation failed: %s", info_log);
        }
    }

    return shader;
}

char *game_load_string(const char *path) {
    FILE *fp = fopen(path, "r");
    fseek(fp, 0, SEEK_END);

    long length = ftell(fp);

    char *buf = malloc(length * sizeof(char));
    fread(buf, sizeof(char), length / sizeof(char), fp);

    fclose(fp);
    return buf;
}

u32 game_Program_load(const char *vertex_src, const char *fragment_src) {
    u32 vertex_shader = create_shader(vertex_src, GL_VERTEX_SHADER);
    u32 fragment_shader = create_shader(fragment_src, GL_FRAGMENT_SHADER);
	u32 program = glCreateProgram();

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	i32 success;
	char info_log[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, info_log);
		PANIC("Program linking failed: %s", info_log);
	}
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}
