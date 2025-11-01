flags=-02 -Wall -std=c2x
ldflags=-lbu

.PHONY: clean

bin:
	mkdir -p bin

all: clean alloc

bin/alloc: bin/alloc.o bin/heap.o | bin
	cc $(flags) $^ -o $@ $(ldflags)

bin/alloc.o: alloc.c alloc.h | bin
	cc $(flags) -c $<

bin/heap.o: heap.asm | bin
	nasm -f elf $^ -o $@

clean:
	rm -f bin/*.o alloc