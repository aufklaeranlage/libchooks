C Dynamic Hooks
===============

[![License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/aufklaeranlage/libchooks/blob/master/LICENSE)

## What this is

This project provides a small framework for writing hooks for dynamically linked functions in (GNU) C.

### Features

* Macro to initialize a struct that holds pre, post and main hooks as well as the orginal function pointer (if needed)
* Macro to register pre, post and main hooks for a function

These Macros can be used over multiple different files since they define weak linked functions that all perform the same actions.

## Installation

1. Clone this repository
2. Compile with `make SRCS="path/to/your/hook/file path/to/second/hook/file"

## Examples

* Simple hook to print arguments passed to write:
    write_pre_hooks.c
    ```c
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
    void static init_write_hooks(void) {
        REGISTER_PRE_HOOK(write, write_pre_hook);
    }
    ```
    write.c
    ```c
    #include <unistd.h>

    int main()
    {
      write(1, "Hello, World!\n", 14);
      return 0;
    }
    ```
    these files also exist in the `examples/` folder in this repository.
    Shell session
    ```bash
    $ make SRCS="examples/write_pre_hooks.c"
    $ gcc examples/write.c
    $ LD_PRELOAD=./libchooks.so ./a.out
    [write] fd: 1, size: 14
    Hello, World!
    ```
Examples for post and main hooks can be found in the examples folder aswell.
