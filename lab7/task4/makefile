#  All Targets
all: run

#Tool invocations
#Executable "fixed_poly.c" depends on the files fixed_poly.o 
run: fixed_poly.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run fixed_poly.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
fixed_poly.o: fixed_poly.c
	gcc -g -Wall -ansi -c -m32 -o fixed_poly.o fixed_poly.c

#Clean the build directory
clean: 
	rm -rf fixed_poly.o run
