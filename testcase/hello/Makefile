CC:= gcc
LD:= ld
CFLAGS = -m32 -static -I../lib/newlib -fno-stack-protector
LDFLAGS = -melf_i386  -e main -L ../lib -static -lc
OBJS := hello

all: hello.o
	$(LD) hello.o -o hello $(LDFLAGS)
	objdump -d hello > hello.txt


clean:
	rm hello hello.o hello.txt
