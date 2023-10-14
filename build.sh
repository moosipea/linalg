#!/usr/bin/sh

CC=gcc
CFLAGS="-Wall -Wextra -pedantic -std=c99"
SOURCES=$(find ./src/*.c -printf "%p ")
GLFW_LIBS=$(pkg-config --static --libs glfw3)
OPENGL_LIBS=$(pkg-config --libs opengl)
LIBS="-lm $GLFW_LIBS $OPENGL_LIBS"
$CC $CFLAGS $LIBS -o main $SOURCES
