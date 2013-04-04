#  All Targets
all: run

#Tool invocations
#Executable "task2a.c" depends on the files task2a.o 
run: task2a.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run task2a.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
task2a.o: task2a.c
	gcc -g -Wall -ansi -c -m32 -o task2a.o task2a.c

#Clean the build directory
clean: 
	rm -rf task2a.o run
