#include "boc.h"

int boc_main(boc *b)
{
    boc_add_exec("build/test");
    boc_add_src("src/test.c");
	boc_add_src("src/clib.c");
    return 0;
}
