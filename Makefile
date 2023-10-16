CC := gcc
INCLUDES := -Isrc/glad/include
CFLAGS := -Wall -Wextra -pedantic -std=c99 $(INCLUDES)
LIBS := -lm `pkg-config --static --libs glfw3` `pkg-config --libs opengl`

ENGINE_SOURCES := src/game.c src/linalg.c src/shader.c
ENGINE_HEADERS := src/game.h src/linalg.h src/shader.h

build: main.o engine.o glad.o
	$(CC) $(LIBS) main.o engine.o glad.o
	rm *.o

main.o: src/main.c
	$(CC) -c $(CFLAGS) src/main.c

engine.o: $(ENGINE_SOURCES) $(ENGINE_HEADERS)
	$(CC) -c $(CFLAGS) $(ENGINE_SOURCES)

glad.o: src/glad/src/glad.c
	$(CC) -c $(INCLUDES) src/glad/src/glad.c

.PHONY: clean
clean:
	rm *.o
