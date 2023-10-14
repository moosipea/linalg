#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <GLFW/glfw3.h>

#include "linalg.h"

typedef uint32_t u32;
typedef float f32;

struct game_Model {
	u32 vertices_count;
	u32 indices_count;
	f32 *vertices;
	u32 *indices;
};

bool game_Model_load(const char *path, struct game_Model *out);

struct game_Transform {
	struct linalg_Vec3 translation;
	struct linalg_Vec3 rotation;
	struct linalg_Vec3 scaling;
};

struct game_Options {
	u32 start_width;
	u32 start_height;
	char *title;
};

struct game_Game {
	GLFWwindow *window;
	struct game_Options opts;
};

int game_Game_run(struct game_Game *game, struct game_Options opts);

enum game_ActorEvent {
	ACTOREVENT_TICK,
	ACTOREVENT_DELETE,
};

struct game_Actor;
struct game_Actor {
	struct game_Transform transform;
	u32 model_handle;
	void (*handler)(struct game_Actor*, struct game_Game*, enum game_ActorEvent);
	void *data;
};

#endif /* GAME_H */
