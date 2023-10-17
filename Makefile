CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99

DEPENDENICES := depend

INCLUDES := -Isrc/glad/include -I$(DEPENDENICES)/glfw/include
LIBPATH := -L$(DEPENDENICES)/glfw/src
LIBS := -lglfw3 -lgdi32 -lopengl32

a.out: depend main.o game.o linalg.o shader.o glad.o
	$(CC) main.o game.o linalg.o shader.o glad.o $(LIBPATH) $(LIBS)

main.o: src/main.c
	$(CC) -c $(CFLAGS) $(INCLUDES) src/main.c

game.o: src/game.c src/game.h
	$(CC) -c $(CFLAGS) $(INCLUDES) src/game.c

linalg.o: src/linalg.c src/linalg.h
	$(CC) -c $(CFLAGS) $(INCLUDES) src/linalg.c

shader.o: src/shader.c src/shader.h
	$(CC) -c $(CFLAGS) $(INCLUDES) src/shader.c

glad.o: src/glad/src/glad.c
	$(CC) -c $(INCLUDES) src/glad/src/glad.c

.PHONY: depend
depend: $(DEPENDENICES)/glfw/src/libglfw3.a

$(DEPENDENICES)/glfw/src/libglfw3.a: $(DEPENDENICES)/glfw
	cmake -G "Unix Makefiles" -B $(DEPENDENICES)/glfw -S $(DEPENDENICES)/glfw \
		-DGLFW_BUILD_EXAMPLES=OFF \
		-DGLFW_BUILD_TESTS=OFF \
		-DGLFW_BUILD_DOCS=OFF
	cmake --build $(DEPENDENICES)/glfw

$(DEPENDENICES)/glfw:
	git clone --depth=1 https://github.com/glfw/glfw.git $(DEPENDENICES)/glfw

.PHONY: clean
clean:
	rm -f *.o