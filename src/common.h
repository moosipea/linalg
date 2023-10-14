#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define PANIC(...) do { \
	fprintf(stderr, "[PANIC] %s:%d:%s: ", __FILE__, __LINE__, __func__); \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, "\n"); \
	exit(EXIT_FAILURE); \
} while (0)

typedef int32_t i32;
typedef uint32_t u32;
typedef float f32;

#endif
