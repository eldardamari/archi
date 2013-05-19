#  All Targets
all: mypipe

#Tool invocations
mypipe: mypipe.o
	@echo 'Linking everything together:'
	gcc -m32 -Wall -ansi mypipe.o -o mypipe
	@echo 'Finished building target: mypipe'
	@echo ' '

#Depends on the source
mypipe.o: mypipe.c
	gcc -m32 -Wall -ansi -c -fno-stack-protector mypipe.c -o mypipe.o

#Clean the build directory
clean: 
	rm -rf mypipe.o mypipe 
