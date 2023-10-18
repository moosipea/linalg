#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "linalg.h"
#include "common.h"

typedef u32 game_Program;

char *game_load_string(const char *path);
game_Program game_Program_load(const char *vertex_src, const char *fragment_src);
void game_Program_set_uniform_Mat4x4(game_Program program, const char *uniform_name, struct linalg_Mat4x4 *mat);

#endif
