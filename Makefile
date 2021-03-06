define colorecho
	@tput setaf 2
	@echo $1
	@tput sgr0
endef

CC       = gcc
CFLAGS   = -Wall -Wextra -mtune=native -g -std=c17
LDFLAGS  = 

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
BinDir	 =./
TARGETS	 = bitwise_ops bin_ops

.PHONY: all
all: $(TARGETS)

swap_test: swap_test.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)
	$(call colorecho,"$@ success. ./\"$@\" to execute.")

bitwise_ops: bitwise_ops.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)
	$(call colorecho,"$@ success. ./\"$@\" to execute.")

bin_ops: bin_ops.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)
	$(call colorecho,"$@ success. ./\"$@\" to execute.")

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true
