#  All Targets
all: run

#Tool invocations
#Executable "linkedlist.c" depends on the files linkedlist.o 
run: linkedlist.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run linkedlist.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
linkedlist.o: linkedlist.c
	gcc -g -Wall -c -m32 -o linkedlist.o linkedlist.c

#Clean the build directory
clean: 
	rm -rf linkedlist.o run
