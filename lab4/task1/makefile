#  All Targets
all: task0

#Tool invocations
#Executable "linkedlist.c" depends on the files linkedlist.o 
task0: start.o util.o main.o
	@echo 'Linking everything together:'
	ld -melf_i386 start.o main.o util.o -o task0
	@echo 'Finished building target: task0'
	@echo ' '

#Depends on the source
start.o: start.s
	nasm -f elf start.s -o start.o

util.o: util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

main.o: main.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector main.c -o main.o

#Clean the build directory
clean: 
	rm -rf start.o util.o main.o task0 
