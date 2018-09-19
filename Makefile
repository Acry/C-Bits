CC       = gcc
CFLAGS   = -Wall -Wextra -mtune=native
LDFLAGS  = 

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
BinDir	 =./
TARGETS	 = bitwise_ops bin_ops

.PHONY: all
all: $(TARGETS)

bitwise_ops: bitwise_ops.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)
bin_ops: bin_ops.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true
