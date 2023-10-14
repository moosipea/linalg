#include "game.h"
#include <stdio.h>

static void print_vertices(f32 *vertices, u32 n) {
	for (u32 i = 0; i < n; i++) {
		printf("%f\n", vertices[i]);
	}
}

static void print_indices(u32 *indices, u32 n) {
	for (u32 i = 0; i < n; i++) {
		printf("%d\n", indices[i]);
	}
}

int main(void) {
	struct game_Game game;
	struct game_Options opts = {
		.start_width = 640,
		.start_height = 480,
		.title = "Hello, world!"
	};

	struct game_Model mdl;
	if (!game_Model_load("res/cube.mdl", &mdl))
		return EXIT_FAILURE;

	print_vertices(mdl.vertices, mdl.vertices_count);
	printf("FIRST: %d\n", mdl.indices[0]);
	print_indices(mdl.indices, mdl.indices_count);

	game_Model_kill(&mdl);

	/* game_Game_run(&game, opts); */

    return EXIT_SUCCESS;
}
