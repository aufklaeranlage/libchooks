NAME := libchooks.so

LCH_SRCS := src/dynamic.c

ifeq ($(SRCS),)
	$(error SRCS not set)
endif

CC := gcc
LDFLAGS := -ldl
CFLAGS := -O2 -fPIC -shared -Iinclude

all:
	$(CC) $(CFLAGS) -o $(NAME) $(LCH_SRCS) $(SRCS) $(LDFLAGS)
