#include "clib.h"

#include <stdio.h>

int main()
{
	clib_arena arena;

	clib_arena_init(&arena, 1024*1024);

	char *data;
	u64 size;

	i32 result = clib_file_read(&arena, "boc.c", &data, &size);


	clib_arena_destroy(&arena);

	return 0;
}
