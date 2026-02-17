#include "boc.h"

int boc_main(boc *b)
{
    boc_add_exec("test");
    boc_add_src("test.c");
	boc_add_src("clib.c");
    return 0;
}
