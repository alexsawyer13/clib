#include "clib.h"

#include <stdio.h>

#define NUM_INTS 10

int main()
{
	clib_arena arena;

	clib_arena_init(&arena, 1024);

	for (int i = 0; i < 1024; i++)
	{
		printf("%d\n", i);
		clib_arena_alloc(&arena, sizeof(int));
	}

	clib_arena_destroy(&arena);

	return 0;
}
