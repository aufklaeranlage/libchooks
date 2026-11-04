#include "chooks/dynamic.h"
#include <unistd.h>
#include <stdio.h>

INIT_HOOK(ssize_t, write, (int, const void *, size_t));

void write_post_hook(void **args, void *result)
{
	ssize_t res = *(ssize_t*)result;
  fprintf(stdout, "[write] return value: %ld\n", res);
}

__attribute__((constructor))
static void init_write_hooks(void) {
  REGISTER_POST_HOOK(write, write_post_hook);
}
