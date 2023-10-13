#!/usr/bin/sh

CC=gcc
CFLAGS="-Wall -Wextra -pedantic -std=c99"
$CC $CFLAGS -lm -o main main.c linalg.c