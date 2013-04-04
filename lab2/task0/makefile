#  All Targets
all: run

#Tool invocations
#Executable "count-words.c" depends on the files count-words.o 
run: count-words.o
	@echo 'Building target: run'
	gcc -g -m32 -Wall -o run count-words.o 
	@echo 'Finished building target: run'
	@echo ' '

#Depends on the source
count-words.o: count-words.c
	gcc -g -Wall -ansi -c -m32 -o count-words.o count-words.c

#Clean the build directory
clean: 
	rm -rf count-words.o run
