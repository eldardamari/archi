#  All Targets
all: run

#Tool invocations
#Executable "reduce.c" depends on the files reduce.o 
run: reduce.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run reduce.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
reduce.o: reduce.c
	gcc -g -Wall -c -m32 -o reduce.o reduce.c

#Clean the build directory
clean: 
	rm -rf reduce.o run
