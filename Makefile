.SUFFIXES: .c .bc

all: popcounts.bc popcounts

popcounts: popcounts.c
	gcc -Wall -Wextra -std=c99 -g -O0 popcounts.c

%.bc : %.c
	clang -g -O1 -c -emit-llvm $< -o $@
