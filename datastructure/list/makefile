LIST_SRCS=$(wildcard *.c)
LIST_OBJS=$(patsubst %.c,%.o,$(LIST_SRCS))

LIST_INCLUDE_DIRS=$(shell pwd)\
				  $(shell pwd)/../../common
LIST_INCLUDE_FLAGS=$(foreach dir_path,$(LIST_INCLUDE_DIRS),-I$(dir_path))

CFLAGS=-Wall -Wextra
CFLAGS+=$(LIST_INCLUDE_FLAGS)
CFLAGS+=-lcunit
CFLAGS_DEBUG=$(CFLAGS) -g
CFLAGS_RELEASE=$(CFLAGS) -O3 -DNDEBUG

list_test.o:$(LIST_SRCS)
	@$(CC) $(LIST_INCLUDE_FLAGS) -o $@ $^

.PHONY:init
init:
	@echo $(CFLAGS)

.PHONY:debug
debug:$(LIST_SRCS)
	@$(CC) $(CFLAGS_DEBUG) -o list_test.o $^

.PHONY:release
release:$(LIST_SRCS)
	@$(CC) $(CFLAGS_RELEASE) -o list_test.o $^

.PHONY:all
all:release

.PHONY:clean
clean:
	@rm -rf *.dSYM
	@rm -f *.o