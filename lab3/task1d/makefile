#  All Targets
all: run

#Tool invocations
#Executable "num_info.c" depends on the files num_info.o 
run: num_info.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run num_info.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
num_info.o: num_info.c
	gcc -g -Wall -c -m32 -o num_info.o num_info.c

#Clean the build directory
clean: 
	rm -rf num_info.o run
