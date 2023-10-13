#ifdef GAME_H
#define GAME_H

struct game_Actor {
	/* TODO transform */
	/* TODO model*/
	void (*handler)(game_Actor*);
	void *data;
}

#endif /* GAME_H */
