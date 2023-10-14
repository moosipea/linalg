#include "game.h"
#include <stdio.h>

int main(void) {
	struct game_Game game;
	struct game_Options opts = {
		.start_width = 640,
		.start_height = 480,
		.title = "Hello, world!"
	};

	game_Game_run(&game, opts);
	
	PANIC("Example panic! width = %d", opts.start_width);

    return EXIT_SUCCESS;
}
