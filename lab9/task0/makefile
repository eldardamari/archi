#  All Targets
all: run

#Tool invocations
#Executable "task0.c" depends on the files task0.o 
run: task0.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run task0.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
task0.o: task0.c
	gcc -g -Wall -ansi -c -m32 -o task0.o task0.c

#Clean the build directory
clean: 
	rm -rf task0.o run
