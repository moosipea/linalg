CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99

DEPENDENICES := depend
SOURCES := src
GLFW_LIB := $(DEPENDENICES)/glfw/src/libglfw3.a

INCLUDES := -I$(SOURCES)/glad/include -I$(DEPENDENICES)/glfw/include
LIBPATH := -L$(DEPENDENICES)/glfw/src
LIBS := -lglfw3 -lgdi32 -lopengl32

a.out: $(GLFW_LIB) main.o game.o linalg.o shader.o glad.o
	$(CC) main.o game.o linalg.o shader.o glad.o $(LIBPATH) $(LIBS)

main.o: $(SOURCES)/main.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $(SOURCES)/main.c

game.o: $(SOURCES)/game.c $(SOURCES)/game.h
	$(CC) -c $(CFLAGS) $(INCLUDES) $(SOURCES)/game.c

linalg.o: $(SOURCES)/linalg.c $(SOURCES)/linalg.h
	$(CC) -c $(CFLAGS) $(INCLUDES) $(SOURCES)/linalg.c

shader.o: $(SOURCES)/shader.c $(SOURCES)/shader.h
	$(CC) -c $(CFLAGS) $(INCLUDES) $(SOURCES)/shader.c

glad.o: $(SOURCES)/glad/src/glad.c
	$(CC) -c $(INCLUDES) $(SOURCES)/glad/src/glad.c

$(GLFW_LIB): $(DEPENDENICES)/glfw
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
	rm -f *.exe