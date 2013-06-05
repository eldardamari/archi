#  All Targets
all: run

#Tool invocations
#Executable "hexeditplus.c" depends on the files hexeditplus.o 
run: hexeditplus.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run hexeditplus.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
hexeditplus.o: hexeditplus.c
	gcc -g -Wall -ansi -c -m32 -o hexeditplus.o hexeditplus.c

#Clean the build directory
clean: 
	rm -rf hexeditplus.o run
