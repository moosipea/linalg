#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
/* #include <GLFW/glfw3.h> */

/* TODO: should use size_t */
struct game_Model {
	uint32_t vertices_count;
	uint32_t indices_count;
	float *vertices;
	uint32_t *indices;
};

bool game_Model_load(const char *path, struct game_Model *out);

/* struct game_Game {
}; */

struct game_Actor;
struct game_Actor {
	/* TODO transform */
	/* TODO model*/
	void (*handler)(struct game_Actor*);
	void *data;
};

#endif /* GAME_H */
