#ifndef _CLIB_H_
#define _CLIB_H_

// Basic types
typedef unsigned long long u64;
typedef unsigned int u32;
typedef long long i64;
typedef int i32;
typedef double f64;
typedef float f32;

_Static_assert (sizeof(u64) == 8, "u64 is not 8 bytes");
_Static_assert (sizeof(u32) == 4, "u32 is not 4 bytes");
_Static_assert (sizeof(i64) == 8, "i64 is not 8 bytes");
_Static_assert (sizeof(i32) == 4, "i32 is not 4 bytes");
_Static_assert (sizeof(f64) == 8, "f64 is not 8 bytes");
_Static_assert (sizeof(f32) == 4, "f32 is not 4 bytes");

// This macro requires <stdlib.h> and <stdio.h>
#define CLIB_ASSERT(condition, msg) do {if (!(condition)) {fprintf(stderr, "Error in %s() %s:%d -> %s\n", __func__, __FILE__, __LINE__, msg); exit(-1);}} while(0)
//#define CLIB_ASSERT(condition, msg) do {} while (0)
#define CLIB_WARNING(msg) do {printf("Warning in %s() %s:%d -> %s\n", __func__, __FILE__, __LINE__, msg); exit(-1);} while(0)

// ---------- Arenas ----------

typedef struct clib_arena
{
	void *data;
	u64   count;
	u64   capacity;
} clib_arena;

void clib_arena_init(clib_arena *a, u64 capacity);
void clib_arena_destroy(clib_arena *a);
void clib_arena_reset(clib_arena *a);
void* clib_arena_alloc(clib_arena *a, u64 size);

// ---------- Vectors ----------

#define CLIB_VECTOR_DEFAULT_COUNT 16

typedef struct clib_vector
{
	void *data;
	u64 count;
	u64 capacity;
	u64 type; // Size in bytes of the type stored in the vector
} clib_vector;

void clib_vector_init(clib_vector *vector, u64 type);
void clib_vector_init_reserve(clib_vector *vector, u64 type, u64 capacity);
void clib_vector_destroy(clib_vector *vector);

void clib_vector_resize(clib_vector *vector, u64 new_capacity);

void *clib_vector_at(clib_vector *vector, u64 index);
void clib_vector_push(clib_vector *vector, void *element);
void clib_vector_pop(clib_vector *vector);

#endif // _CLIB_H_
