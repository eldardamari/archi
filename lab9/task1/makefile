#  All Targets
all: run

#Tool invocations
#Executable "print.c" depends on the files print.o 
run: print.o
	@echo 'Building target: run'
	ld -o print print.o startup.o start.o -L/usr/lib32 -lc -T linking_script -dynamic-linker /lib32/ld-linux.so.2
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
print.o: print.c
	gcc -m32 -c print.c -o print.o

#Clean the build directory
clean: 
	rm -rf print.o run
