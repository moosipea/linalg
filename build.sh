#!/usr/bin/sh

CC=gcc
CFLAGS="-Wall -Wextra -pedantic -std=c99"
SOURCES=$(find ./src/*.c -printf "%p ")
GLFW_LIBS=$(pkg-config --static --libs glfw3)
LIBS="-lm $GLFW_LIBS"
$CC $CFLAGS $LIBS -o main $SOURCES
