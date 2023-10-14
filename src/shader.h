#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "common.h"

char *game_load_string(const char *path);
u32 game_Program_load(const char *vertex_src, const char *fragment_src);

#endif
