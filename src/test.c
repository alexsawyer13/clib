#include "clib.h"

#include <stdio.h>

#define NUM_INTS 10

int main()
{
	clib_prng rng = {0};
	clib_prng_init(&rng);

	for (int i = 0; i < NUM_INTS; i++) {
		printf("%d\n", clib_prng_rand_u32_range(&rng, 2, 4));
	}

	return 0;
}
