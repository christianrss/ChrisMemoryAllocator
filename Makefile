CFLAGS=-O2 -Wall -std=c23 -m32
LDFLAGS=-lbu

.PHONY: all clean

bin:
	mkdir -p bin

all: clean bin/alloc

bin/alloc: bin/alloc.o bin/heap.o | bin
	cc $(CFLAGS) $^ -o $@ $(LDFLAGS)

bin/alloc.o: alloc.c alloc.h | bin
	cc $(CFLAGS) -c $< -o $@

bin/heap.o: heap.asm | bin
	nasm -f elf $< -o $@

clean:
	rm -f ./bin/*.o ./bin/alloc