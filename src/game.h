#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
/* #include <GLFW/glfw3.h> */

struct Model {
	size_t vertex_count;
	size_t index_count;
	float *vertices;
	size_t *indices;
};

void game_Model_load(const char *path);

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
