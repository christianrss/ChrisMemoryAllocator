# ChrisMemoryAllocator
Just my own Memory Allocator written from scratch in C


sudo apt install gcc-14 gcc-14-multilib libc6-dev-i386

gdb settings

set enable-bracketed-paste off
set style enable off
set disassembly-flavor intel

define f
target exec
target exec ./bin/alloc
symbol-fle ./bin/alloc
end

define xx
x/30i ($eip-20)
end

define clear
!clear
end

start
r
f
run

bt
xx

i r eax

x/x