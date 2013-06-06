#  All Targets
all: run

#Tool invocations
#Executable "poly.c" depends on the files poly.o 
run: poly.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run poly.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
poly.o: poly.c
	gcc -g -Wall -ansi -c -m32 -o poly.o poly.c

#Clean the build directory
clean: 
	rm -rf poly.o run
