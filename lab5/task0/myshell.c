#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "LineParser.h"

#define PATH_MAX 2048
#define STR_MAX 2048

/*Fucntions declarations*/
void execute(cmdLine *pCmdLine);

int main (int argc , char* argv[], char* envp[]) {
    
    /*Parameters*/
    char *buf[PATH_MAX];
    char *buf1[PATH_MAX];
    char str[STR_MAX];
    cmdLine *command_struct;

    /*Displaying a prompt - current directory
     * savig the current directory         */
    *buf1 = getwd(buf);

    while (1)
    {
    
        printf("%s > ", *buf1);
        fgets(str,STR_MAX,stdin);

        /*quiting*/
        if( strcmp(str, "quit\n") == 0)
            break;

        /*Parsing string line*/
        command_struct = parseCmdLines(str); 
        execute(command_struct);
    }
    return 0; 
}

/*This function execute the parsed line with the execv system_call */
void execute(cmdLine *pCmdLine) {

    /*executing the program*/
    if(execvp(pCmdLine->arguments[0],pCmdLine->arguments) == -1)
        perror("");

    /*Releasing allocated memory*/
    freeCmdLines(pCmdLine);
}
