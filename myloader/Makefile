CC = gcc
CFLAGS = -m32 -O2 -Wall -Werror -fno-builtin
CFLAGS += -I./include  # TODO: Add an option here to add the directory
                    # "myloader/include" to search for header files.
ASFLAGS = -m32
 
CSRC = $(shell find src/ -name "*.c")  # TODO: Find all .c files under the "myloader/src" directory.
 
OBJS = $(CSRC:.c=.o)  # TODO: Convert the suffix of all string in $(CSRC) into ".o".
 
# TODO: Add prerequisites for creating the loader.
loader: $(OBJS) src/start.o
	ld -o loader -e start -Ttext 0x100000 -m elf_i386 src/start.o $(OBJS)
 
clean:
	rm $(OBJS) loader # TODO: Add command to remove all compile results.
