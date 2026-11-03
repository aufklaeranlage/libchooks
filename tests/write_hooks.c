#include "chooks.h"
#include <unistd.h>
#include <stdio.h>

INIT_HOOK(ssize_t, write, (int, const void *, size_t));

void write_pre_hook(void **args)
{
  int fd = *(int*)args[0];
  size_t size = *(size_t*)args[2];
  fprintf(stdout, "[write] fd: %d, size: %lu\n", fd, size);
}

__attribute__((constructor))
void init_write_hooks(void) {
  REGISTER_PRE_HOOK(write, write_pre_hook);
}
