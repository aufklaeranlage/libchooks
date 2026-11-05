#include "chooks.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

INIT_HOOK(ssize_t, write, (int, const void *, size_t));

char *to_hex(char c) {
	const char hex[17] = "0123456789abcdef";
	static char ret[5] = "0x  ";
	ret[3] = hex[c / 16];
	ret[2] = hex[c % 16];
	return ret;
}

void write_main_hook(void **args, void *result)
{
	const char *buf = *(char **)args[1];
	int buflen = strlen(buf);
	int ret = 0;
	for (int i = 0; i < buflen; ++i) {
		if (i != 0) {
			ret += real_write(1, " ", 1);
		}
		ret += real_write(1, to_hex(buf[i]), 4);
	}
	ret += real_write(1, "\n", 1);
	*(size_t *)result = ret;
}

__attribute__((constructor))
static void init_write_hooks(void) {
  REGISTER_MAIN_HOOK(write, write_main_hook);
}
