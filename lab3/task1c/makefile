#  All Targets
all: run

#Tool invocations
#Executable "map.c" depends on the files map.o 
run: map.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run map.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
map.o: map.c
	gcc -g -Wall -c -m32 -o map.o map.c

#Clean the build directory
clean: 
	rm -rf map.o run
