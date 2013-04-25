#  All Targets
all: task1

#Tool invocations
#Executable "linkedlist.c" depends on the files linkedlist.o 
task1: start.o util.o my_cut.o
	@echo 'Linking everything together:'
	ld -melf_i386 start.o my_cut.o util.o -o task1
	@echo 'Finished building target: task1'
	@echo ' '

#Depends on the source
start.o: start.s
	nasm -f elf start.s -o start.o

util.o: util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

my_cut.o: my_cut.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector my_cut.c -o my_cut.o

#Clean the build directory
clean: 
	rm -rf start.o util.o my_cut.o task1 
