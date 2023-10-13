#!/usr/bin/sh

CC=gcc
CFLAGS="-Wall -Wextra -pedantic -std=c99"
SOURCES=$(find ./src/*.c -printf "%p ")
$CC $CFLAGS -lm -o main $SOURCES
