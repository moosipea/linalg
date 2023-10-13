#include "game.h"
#include <stdio.h>

int main(void) {
	struct game_Model model;
	if (!game_Model_load("res/out.mdl", &model)) {
		printf("Failed to load model!\n");
		return 1;
	}
    return 0;
}
