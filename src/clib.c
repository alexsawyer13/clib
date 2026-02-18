#include "clib.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// ---------- Arenas ----------

void clib_arena_init(clib_arena *a, u64 capacity)
{
	CLIB_ASSERT(a, "a is NULL");
	CLIB_ASSERT(capacity > 0, "Capacity is 0");
	CLIB_ASSERT(a->data == NULL, "Already has data!");
	a->data = malloc(capacity);
	CLIB_ASSERT(a->data, "malloc failed");
	a->capacity = capacity;
	a->count = 0;
}

void clib_arena_destroy(clib_arena *a)
{
	CLIB_ASSERT(a, "a is NULL");
	CLIB_ASSERT(a->data, "a has no data");
	free(a->data);
	a->capacity = 0;
	a->count = 0;
	a->data = NULL;
}

void clib_arena_reset(clib_arena *a)
{
	CLIB_ASSERT(a, "a is NULL");
	a->count = 0;
}

void* clib_arena_alloc(clib_arena *a, u64 size)
{
	CLIB_ASSERT(a, "a is NULL");
	CLIB_ASSERT(size > 0, "size is 0");
	if (a->count + size > a->capacity)
	{
		CLIB_WARNING("Arena is full");
		return NULL;
	}
	void *ret = a->data + a->count;
	a->count += size;
	return ret;
}

// ---------- Vectors ----------

void clib_vector_init(clib_vector *vector, u64 type)
{
	clib_vector_init_reserve(vector, type, CLIB_VECTOR_DEFAULT_COUNT);
}

void clib_vector_init_reserve(clib_vector *vector, u64 type, u64 capacity)
{
	CLIB_ASSERT(vector, "vector is NULL");
	CLIB_ASSERT(type > 0, "type has size 0");
	CLIB_ASSERT(capacity > 0, "capacity has size 0");
	CLIB_ASSERT(vector->data == NULL, "Already has data!");

	vector->data = malloc(type * capacity);
	CLIB_ASSERT(vector->data, "malloc failed");

	vector->type = type;
	vector->count = 0;
	vector->capacity = capacity;
}

void clib_vector_destroy(clib_vector *vector)
{
	CLIB_ASSERT(vector, "vector is NULL");
	CLIB_ASSERT(vector->data, "vector has no data");
	free(vector->data);
	vector->data = NULL;
	vector->type = 0;
	vector->capacity = 0;
	vector->count = 0;
}

void clib_vector_resize(clib_vector *vector, u64 new_capacity)
{
	CLIB_ASSERT(vector, "vector is NULL");
	CLIB_ASSERT(vector->data, "vector has no data");
	CLIB_ASSERT(vector->type > 0, "type has size 0");
	CLIB_ASSERT(vector->capacity > 0, "capacity has size 0");
	CLIB_ASSERT(new_capacity > 0, "new_capacity has size 0");

	void *new = realloc(vector->data, new_capacity * vector->type);
	CLIB_ASSERT(new, "realloc failed");

	vector->data = new;
	vector->capacity = new_capacity;
}

void *clib_vector_at(clib_vector *vector, u64 index)
{
	CLIB_ASSERT(vector, "vector is NULL");
	CLIB_ASSERT(vector->data, "vector has no data");
	CLIB_ASSERT(vector->type > 0, "type has size 0");
	CLIB_ASSERT(vector->capacity > 0, "capacity has size 0");
	CLIB_ASSERT(vector->count > index, "index out of bounds!");
	return vector->data + index * vector->type;
}

void clib_vector_push(clib_vector *vector, void *element)
{
	CLIB_ASSERT(vector, "vector is NULL");
	CLIB_ASSERT(element, "element is NULL");
	CLIB_ASSERT(vector->data, "vector has no data");
	CLIB_ASSERT(vector->type > 0, "type has size 0");
	CLIB_ASSERT(vector->capacity > 0, "capacity has size 0");

	if (vector->count + 1 > vector->capacity)
	{
		clib_vector_resize(vector, vector->capacity * 2);
	}

	memcpy(vector->data + vector->count * vector->type, element, vector->type);
	vector->count++;
}

void clib_vector_pop(clib_vector *vector)
{
	CLIB_ASSERT(vector, "vector is NULL");
	CLIB_ASSERT(vector->data, "vector has no data");
	CLIB_ASSERT(vector->type > 0, "type has size 0");
	CLIB_ASSERT(vector->capacity > 0, "capacity has size 0");
	CLIB_ASSERT(vector->count > 0, "capacity has size 0");

	vector->count--;
}

// ---------- Random numbers ----------

void clib_prng_init(clib_prng *rng)
{
	CLIB_ASSERT(rng, "rng is NULL");
	clib_prng_init_seed(rng, (u64)time(NULL), (u64)&clib_prng_init_seed);
}

void clib_prng_init_seed(clib_prng *rng, u64 initstate, u64 initseq)
{
	CLIB_ASSERT(rng, "rng is NULL");
	rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    clib_prng_rand_u32(rng);
    rng->state += initstate;
    clib_prng_rand_u32(rng);
}

u32 clib_prng_rand_u32(clib_prng *rng)
{
	CLIB_ASSERT(rng, "rng is NULL");
    u64 oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    u32 xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    u32 rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

u32 clib_prng_rand_u32_range(clib_prng *rng, u32 min, u32 max)
{
	CLIB_ASSERT(max > min, "max !> min");
	return clib_prng_rand_u32(rng) % (max - min + 1) + min;
}

i32 clib_prng_rand_i32_range(clib_prng *rng, i32 min, i32 max)
{
	CLIB_ASSERT(max > min, "max !> min");
	return (i32)((i64)clib_prng_rand_u32(rng) % (i64)(max - min + 1) + (i64)min);
}

f32 clib_prng_rand_f32(clib_prng *rng)
{
	return ((f32)clib_prng_rand_u32(rng))/((f32)((u32)-1));
}
