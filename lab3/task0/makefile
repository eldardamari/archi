#  All Targets
all: run

#Tool invocations
#Executable "bubblesort.c" depends on the files bubblesort.o 
run: bubblesort.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run bubblesort.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
bubblesort.o: bubblesort.c
	gcc -g -Wall -c -m32 -o bubblesort.o bubblesort.c

#Clean the build directory
clean: 
	rm -rf bubblesort.o run
