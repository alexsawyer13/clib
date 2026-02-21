#include "clib.h"

#include <stdio.h>

int main()
{
	clib_arena *arena;

	arena = clib_arena_init(1024*1024);

	int *ptr = clib_arena_alloc(arena, 100 * sizeof(int));



	clib_arena_destroy(&arena);

	return 0;
}
