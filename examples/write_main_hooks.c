#include "chooks.h"
#include <unistd.h>
#include <stdio.h>

INIT_HOOK(ssize_t, write, (int, const void *, size_t));

void write_main_hook(void **args, void *result)
{
	const char *buf = *(char **)args[1];
	ssize_t *res = (ssize_t*)result;
  *res = fprintf(stdout, "[write] buffer: %s\n", buf);
}

__attribute__((constructor))
static void init_write_hooks(void) {
  REGISTER_MAIN_HOOK(write, write_main_hook);
}
