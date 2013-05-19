#  All Targets
all: mypipeline

#Tool invocations
mypipeline: mypipeline.o
	@echo 'Linking everything together:'
	gcc -m32 -Wall -ansi mypipeline.o -o mypipeline
	@echo 'Finished building target: mypipeline'
	@echo ' '

#Depends on the source
mypipeline.o: mypipeline.c
	gcc -m32 -Wall -ansi -c -fno-stack-protector mypipeline.c -o mypipeline.o

#Clean the build directory
clean: 
	rm -rf mypipeline.o mypipeline 
