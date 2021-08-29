.PHONY: all clean

all: fork-example tree-example ask2-fork ask2-signals ask1-given-tree ask3-expr-tree

CC = gcc
CFLAGS = -g -Wall -O2
SHELL= /bin/bash

tree-example: tree-example.o tree.o
	$(CC) $(CFLAGS) $^ -o $@

fork-example: fork-example.o proc-common.o
	$(CC) $(CFLAGS) $^ -o $@

ask2-fork: ask2-fork.o proc-common.o tree.o
	$(CC) $(CFLAGS) $^ -o $@

ask2-signals: ask2-signals.o proc-common.o tree.o
	$(CC) $(CFLAGS) $^ -o $@

ask1-given-tree: ask1-given-tree.o proc-common.o
	$(CC) $(CFLAGS) $^ -o $@

ask3-expr-tree: ask3-expr-tree.o proc-common.o tree.o
	$(CC) $(CFLAGS) $^ -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S -fverbose-asm $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.i: %.c
	gcc -Wall -E $< | indent -kr > $@

clean:
	rm -f *.o tree-example fork-example pstree-this ask2-{fork,tree,signals,pipes} ask1-given-tree ask3-expr-tree
