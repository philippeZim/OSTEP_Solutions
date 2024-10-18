CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wsign-conversion -O3

PROGRAMS = memory-user

SRC = $(PROGRAMS:=.c)
OBJ = $(PROGRAMS:=.o)
TARGETS = $(PROGRAMS)

$(TARGETS): %: %.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGETS)
