LIBXTHREAD_STATIC=libxthread.a
XTHREAD_ASM_SRCS=context_switch.S
XTHREAD_C_SRCS=xthread.c
XTHREAD_OBJS=$(patsubst %.c,%_c.o,$(XTHREAD_C_SRCS))\
			 $(patsubst %.S,%_S.o,$(XTHREAD_ASM_SRCS))

XTHREAD_EXAMPLE_DIR=example
XTHREAD_EXAMPLE_SRCS=example/main.c
XTHREAD_EXAMPLE_OBJS=$(patsubst %.c,%.o,$(XTHREAD_EXAMPLE_SRCS))

CFLAGS = -g -march=x86-64
XTHREAD_INCLUDE_DIRS=.
XTHREAD_INCLUDE_DIR_FLAGS=$(foreach dir,$(XTHREAD_INCLUDE_DIRS),-I$(dir))
XTHREAD_LINK_DIRS=.
XTHREAD_LINK_DIR_FLAGS=$(foreach dir,$(XTHREAD_LINK_DIRS),-L$(dir))
EXAMPLE_CFLAGS=$(CFLAGS)
EXAMPLE_CFLAGS+=$(CFLAGS) \
			   $(XTHREAD_INCLUDE_DIR_FLAGS) \
			   $(XTHREAD_LINK_DIR_FLAGS)
EXAMPLE_CFLAGS+=-lxthread

init:
	@echo $(XTHREAD_INCLUDE_DIR_FLAGS)

%_c.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $^

%_S.o : %.S
	@$(CC) $(CFLAGS) -o $@ -c $^

$(LIBXTHREAD_STATIC):$(XTHREAD_OBJS)
	@$(AR) rcs $@ $^

$(XTHREAD_EXAMPLE_DIR)/%.o : $(XTHREAD_EXAMPLE_DIR)/%.c
	@$(CC) $(EXAMPLE_CFLAGS) -o $@ $^

.PHONY:all
all:$(LIBXTHREAD_STATIC) $(XTHREAD_EXAMPLE_OBJS)

.PHONY:clean
clean:
	@rm -f *.o
	@rm -f $(XTHREAD_EXAMPLE_OBJS)
	@rm -f *.a
	@rm -rf *.dSYM $(XTHREAD_EXAMPLE_DIR)/*.dSYM
