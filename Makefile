CC := gcc
INCLUDES := -Isrc/glad/include
CFLAGS := -Wall -Wextra -pedantic -std=c99 $(INCLUDES)
LIBS := -lm `pkg-config --static --libs glfw3` `pkg-config --libs opengl`

build: main.o game.o glad.o linalg.o shader.o
	$(CC) $(LIBS) main.o game.o glad.o linalg.o shader.o
	rm *.o

main.o: src/main.c
	$(CC) -c $(CFLAGS) src/main.c

game.o: src/game.c src/game.h
	$(CC) -c $(CFLAGS) src/game.c

glad.o: src/glad/src/glad.c
	$(CC) -c $(INCLUDES) src/glad/src/glad.c

linalg.o: src/linalg.c src/linalg.h
	$(CC) -c $(CFLAGS) src/linalg.c

shader.o: src/shader.c src/shader.h
	$(CC) -c $(CFLAGS) src/shader.c

.PHONY: clean
clean:
	rm *.o
