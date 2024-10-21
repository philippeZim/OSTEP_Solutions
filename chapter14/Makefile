CC = gcc

CFLAGS = -g -Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wsign-conversion -O2

PROGRAMS = null no-free bounds aufgabe6 aufgabe8

SRC = $(PROGRAMS:=.c)
OBJ = $(PROGRAMS:=.o)
TARGETS = $(PROGRAMS)

.PHONY: all
all: $(TARGETS)

$(TARGETS): %: %.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGETS)
