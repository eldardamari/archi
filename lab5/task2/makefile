#  All Targets
all: myshell

#Tool invocations
myshell: LineParser.o LinkedList.o myshell.o
	@echo 'Linking everything together:'
	gcc -m32 -Wall -ansi myshell.o LineParser.o LinkedList.o -o myshell
	@echo 'Finished building target: myshell'
	@echo ' '

#Depends on the source
LineParser.o: LineParser.c
	gcc -m32 -Wall -ansi -c -fno-stack-protector LineParser.c -o LineParser.o

LinkedList.o: LinkedList.c
	gcc -m32 -Wall -ansi -c -fno-stack-protector LinkedList.c -o LinkedList.o

myshell.o: myshell.c
	gcc -m32 -Wall -ansi -c -fno-stack-protector myshell.c -o myshell.o

#Clean the build directory
clean: 
	rm -rf start.o LineParser.o LinkedList.o myshell.o myshell 
