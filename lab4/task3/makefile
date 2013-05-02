#  All Targets
all: patch

#Tool invocations
#Executable "linkedlist.c" depends on the files linkedlist.o 
patch: start.o util.o patch.o
	@echo 'Linking everything together:'
	ld -melf_i386 start.o patch.o util.o -o patch
	@echo 'Finished building target: patch'
	@echo ' '

#Depends on the source
start.o: start.s
	nasm -f elf start.s -o start.o

util.o: util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

patch.o: patch.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector patch.c -o patch.o

#Clean the build directory
clean: 
	rm -rf start.o util.o patch.o patch 
