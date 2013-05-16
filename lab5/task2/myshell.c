#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "LineParser.h"
#include "LinkedList.h"

#define PATH_MAX 2048
#define STR_MAX 2048

/*Fucntions declarations*/
void execute(cmdLine *pCmdLine);
void historylog(char** history,char* str,int* count_history);
void printhistory(char** history, int* count_history);
void freehistory(char** history, int* count_history);
int checkForReplacment(cmdLine* pCmdLine,int i);

int main (int argc , char* argv[], char* envp[]) {
    
    /*Parameters*/
    char *buf[PATH_MAX];
    char *buf1[PATH_MAX];
    char str[STR_MAX];
    cmdLine *command_struct;
    char **history;
    int count_history;
    int i,num;
    varset *head_varset = NULL;
    int arg_to_change = -1;
    char *substring;
    int arguments;

    history = (char**)malloc(10*sizeof(char*));
    
    /*Distrplaying a prompt - current directory
     * savig the current directory         */
    *buf1 = getwd(buf);

    while (1)
    {
        printf("%s :P ", *buf1);
        fgets(str,STR_MAX,stdin);

        /*quiting*/
        if( strcmp(str, "quit\n") == 0) {
            freehistory(history,&count_history);
            freeall(head_varset);
            free(head_varset);
            break;
        }

        /*Handling entring just Enter*/
        if( strcmp(str, "\n") == 0)
            continue;

        /*Will to use '!' command?*/
        if( *str == '!' && (int)str[1] >= 48 && (int)str[1] <= 57
                && (int)str[1]-48 >= 0 && (int)str[1]-48 <= count_history-1){
            /* copy char by char to str */
            num = (int)str[1] - 48;
            for(i=0 ; i <= strlen(history[num]) ; i++){
                str[i] = history[num][i];
            }
        }
        
        /*Adding to double array command */
        historylog(history,str,&count_history);        

        /*Parsing string line*/
        command_struct = parseCmdLines(str); 
        

                

        /*Will to use 'set' command?*/
        if(strcmp(command_struct->arguments[0],"set") == 0 && 
                command_struct->argCount == 3) {

            addLink(&head_varset,
                    command_struct->arguments[1],
                    command_struct->arguments[2]);

            /*free the command*/
            freeCmdLines(command_struct);
            continue;
        }
        
        /*printing the envirioment variables*/
        if(strcmp(command_struct->arguments[0],"env") == 0){
            printall(head_varset);
            continue;
        }
        

        /*Check if arguments have & in them */
        if ((arguments = command_struct->argCount) >= 2) {

            while ((arguments-1) > 0) {

                arg_to_change = checkForReplacment(command_struct,arguments-1);
                if(arg_to_change != -1){ 
                    substring = (char*)malloc(
                            strlen(command_struct->arguments[arg_to_change])-1);
                    strcpy(substring,
                            &command_struct->arguments[arg_to_change][1]);

                    replaceCmdArg(command_struct,arg_to_change,
                            getName(head_varset,substring));

                    /*deallocation temp string*/
                    free(substring);
                }
                arguments--;
            }
        }
        
        /*removing a vriable fron envirioment*/
        if(strcmp(command_struct->arguments[0],"unset") == 0 &&
                command_struct->argCount == 2){
            findAndDestoryLink(head_varset,
                               command_struct->arguments[1]);
            continue;
        }

        /*Will to use 'mygecko' command?*/
        if(strcmp(command_struct->arguments[0],"mygecko") == 0) {
            replaceCmdArg(command_struct,0,"echo");
        }
        
        /*Will to use 'cd' command?*/
        if(strcmp(command_struct->arguments[0],"cd") == 0) {
            if(chdir(command_struct->arguments[1]) == -1) {
                printf("Are you out of your mind?!..\n");
            }
            else {
                freeCmdLines(command_struct);
                *buf1 = getwd(buf);
            }
        }
        else {
            if (strcmp(command_struct->arguments[0],"history") != 0){
                execute(command_struct);
                /* deallocating struct command */
                freeCmdLines(command_struct);
            }
        }
        
        /*Will to use 'history' command?*/
        if(strcmp(command_struct->arguments[0],"history") == 0) {
            printhistory(history,&count_history);
        }
     
        /* deallocating struct command */
        freeCmdLines(command_struct);
    }
        /* deallocating struct command */
        freeCmdLines(command_struct);
    return 0; 
}

/*This function execute the parsed line with the execv system_call */
void execute(cmdLine *pCmdLine) {

    pid_t pid;

    if(!(pid = fork())) {

        /*executing the program*/
        if(execvp(pCmdLine->arguments[0],pCmdLine->arguments) == -1) {
            perror("error with execvp");
            _exit(EXIT_FAILURE);
        }

        /*Releasing allocated memory*/
        freeCmdLines(pCmdLine);
    }
    else {

        if(pCmdLine->blocking != 0)
            waitpid(pid,NULL,0);
    }
}

/*Logging the 10th last commands entered by user*/
void historylog(char** history,char* str,int* size) {

    int i;

    if((*size) == 0){
        history[0] = (char*)malloc((strlen(str)+1)*sizeof(char)); 
        strcpy(history[0],str);
        (*size)++;
        return;
    } 
    else
        if((*size)==10){
       
            free(history[9]);
            for(i=9 ; i > 0 ; i--) {
                history[i] = history[i-1];
                history[i-1] = NULL;
            }
            history[0] = malloc((strlen(str)+1)*sizeof(char)); 
            strcpy(history[0],str);
        }
        else {
            for(i=(*size) ; i > 0 ; i--) {
                history[i] = history[i-1];
                history[i-1] = NULL;
            }
            history[0] = malloc((strlen(str)+1)*sizeof(char)); 
            strcpy(history[0],str);
            (*size)++;
        }
    }

/*Printing array of commands*/
void printhistory(char **history,int* size) {
   
    int i;
    
    for(i=0 ; i <= (*size)-1 ; i++) {
        printf("#%d -> %s",i,history[i]);
    }
}

/*freehistory*/
void freehistory(char** history, int* size) {

    int i = 9;

    for(; i>=0 ; i--) {
        free(history[i]);
    }
    free(history);
}

/* look for $ in srguments */
int checkForReplacment(cmdLine* pCmdLine,int i){

    /*int i;
    for(i = 1 ; i < pCmdLine->argCount ; i++){*/

        if(pCmdLine->arguments[i][0] == '$')
            return i;
        return -1;
}
