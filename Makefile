CC := gcc
INCLUDES := -Isrc/glad/include
LIBS := -lm `pkg-config --static --libs glfw3` `pkg-config --libs opengl`
CFLAGS := -Wall -Wextra -pedantic -std=c99 $(INCLUDES) $(LIBS)

build: main.o game.o glad.o linalg.o
	$(CC) $(CFLAGS) main.o game.o glad.o linalg.o

main.o: src/main.c
	$(CC) -c $(INCLUDES) src/main.c

game.o: src/game.c src/game.h
	$(CC) -c $(INCLUDES) src/game.c

glad.o: src/glad/src/glad.c
	$(CC) -c $(INCLUDES) src/glad/src/glad.c

linalg.o: src/linalg.c src/linalg.h
	$(CC) -c $(INCLUDES) src/linalg.c

.PHONY: clean
clean:
	rm ./*.o
