INLINE_ASM_C_SRC=$(wildcard *.c)
INLINE_ASM_OBJS=$(patsubst %.c,%.o,$(INLINE_ASM_C_SRC))
CFLAGS=-g
CFLAGS+=-O0 -Wall -Wextra

%.o:%.c
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY:all
all:$(INLINE_ASM_OBJS)

.PHONY:clean
clean:
	@$(RM) -f $(INLINE_ASM_OBJS)
	@$(RM) -rf *.dSYM
	@$(RM) -f *.txt
