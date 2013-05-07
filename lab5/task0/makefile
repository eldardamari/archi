#  All Targets
all: myshell

#Tool invocations
myshell: LineParser.o myshell.o
	@echo 'Linking everything together:'
	gcc -m32 -Wall -ansi myshell.o LineParser.o -o myshell
	@echo 'Finished building target: myshell'
	@echo ' '

#Depends on the source
LineParser.o: LineParser.c
	gcc -m32 -Wall -ansi -c -fno-stack-protector LineParser.c -o LineParser.o

myshell.o: myshell.c
	gcc -m32 -Wall -ansi -c -fno-stack-protector myshell.c -o myshell.o

#Clean the build directory
clean: 
	rm -rf start.o LineParser.o myshell.o myshell 
