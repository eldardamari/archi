#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include "LineParser.h"
#include "LinkedList.h"
#include "Utils.h"

#define PATH_MAX 2048
#define STR_MAX 2048

/*Fucntions declarations*/
void execute(cmdLine *pCmdLine);
void executeWithPipes(cmdLine *pCmdLine, int **pipesfd,int number_of_pipes);
void historylog(char** history,char* str,int* count_history);
void printhistory(char** history, int* count_history);
void freehistory(char** history, int* count_history);
int checkForReplacment(cmdLine* pCmdLine,int i);
int howManyPipes(cmdLine* pCmdLine);
void executeWithSinglePipe(cmdLine *pCmdLine);

int main (int argc , char* argv[], char* envp[]) {
    
    /*Parameters*/
    char buf[PATH_MAX];
    char str[STR_MAX];
    cmdLine *command_struct;
    char **history;
    int count_history;
    int i,num;
    varset *head_varset = NULL;
    int arg_to_change = -1;
    char *substring;
    int arguments;
    int working_with_pipes = 0;
    int number_of_pipes;

    int **pipesfd;

    /* allocating fixed allocated memory for hisotry log*/
    history = (char**)malloc(10*sizeof(char*));
    count_history = 0;
    
    /*Displaying a prompt - current directory
     * savig the current directory         */
    getwd(buf);

    while (1)
    {
        /*Printing command path name in blue color*/
        printf("\033[22;34m %s :> \033[0m", buf);

        fgets(str,STR_MAX,stdin);

        /*quiting*/
        if( strcmp(str, "quit\n") == 0) {
            freehistory(history,&count_history);
            if(head_varset != NULL)
                freeall(head_varset);
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
        /*Saving all histort in log */
        historylog(history,str,&count_history);

        /*Parsing string line*/
        command_struct = parseCmdLines(str); 
        
        /* Checking if comand with one pipe*/
        working_with_pipes = 0;
        /*this is the right place for working on pipe?*/
        if (command_struct->next != NULL) {

            working_with_pipes = 1;
            number_of_pipes = 0;
            number_of_pipes = howManyPipes(command_struct);
            pipesfd = createPipes(number_of_pipes);
        }

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
        
        /*removing a vriable from envirioment*/
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
                getwd(buf);
                continue;
            }
        }
        else {
            /*Checking for history command */
            if (strcmp(command_struct->arguments[0],"history") != 0){
                /* ececuting */
                if(working_with_pipes) {
                    executeWithPipes(command_struct,pipesfd,number_of_pipes);
                    continue;
                }
                execute(command_struct);
                /* deallocating struct command */
                freeCmdLines(command_struct);
                continue;
            }
        }
        
        /*Will to use 'history' command?*/
        if(strcmp(command_struct->arguments[0],"history") == 0) {
            printhistory(history,&count_history);
            freeCmdLines(command_struct);
        }
     
    }
    return 0; 
}

/*This function execute the parsed line with the execv system_call */
void execute(cmdLine *pCmdLine) {

    printf("regular exe \n");

    int pipefd[2];
    pid_t pid;
    int fd_input,fd_output;

    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if(!(pid = fork())) {

        /*lets check if need to use the redirectInput*/
        if(pCmdLine->inputRedirect != NULL){
            close(0);
            fd_input = open(pCmdLine->inputRedirect,O_RDONLY, 0700);
            if(fd_input== -1){
                perror("input_fail");
                exit(EXIT_FAILURE);
            }
        }
        if(pCmdLine->outputRedirect != NULL){
            close(1);
            fd_output = open(pCmdLine->outputRedirect, O_CREAT | O_WRONLY | O_APPEND, 0700);
            if(fd_output == -1){
                perror("output_fail");
                exit(EXIT_FAILURE);
            }
        }

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

    int i; 

    for(i=0; i < (*size) ; i++) {
        free(history[i]);
    }
    free(history);
}

/* look for $ in srguments */
int checkForReplacment(cmdLine* pCmdLine,int i){

        if(pCmdLine->arguments[i][0] == '$')
            return i;
        return -1;
}

int howManyPipes(cmdLine* pCmdLine) {

    int i=0;
    while (pCmdLine->next) {
        i++;
        pCmdLine = pCmdLine->next;
    }
    return i;
}
/*FIXME  Working in this function,for now there is a problem with the pipes array
look in the for loop, the index of pipesfd array need to be collarated with command
in a good way*/
void executeWithPipes(cmdLine *pCmdLine, int **pipesfd,int number_of_pipes) {

    int pipeOut_dup;
    int pipeIn_dup;
    pid_t cpid;
    pid_t cpid2;
    int index = 0;
    int fd_input,fd_output;
    
 
    for(index = 0 ; index <= number_of_pipes ; index++) {

        if (pCmdLine == NULL)
            return;
    
        if(!(cpid = fork())) {

        /*[>lets check if need to use the redirectInput<]*/
        if(pCmdLine->inputRedirect != NULL){
            close(0);
            fd_input = open(pCmdLine->inputRedirect,O_RDONLY, 0700);
            if(fd_input== -1){
                perror("input_fail");
                exit(EXIT_FAILURE);
            }
        }

        /*[>Handling redirectOutput<]*/
        if(pCmdLine->outputRedirect != NULL){
            close(1);
            fd_output = open(pCmdLine->outputRedirect, O_CREAT | O_WRONLY , 0700);
            if(fd_output == -1){
                perror("output_fail");
                exit(EXIT_FAILURE);
            }
            /*[>executing the program<]*/
            if(execvp(pCmdLine->arguments[0],pCmdLine->arguments) == -1) {
                perror("error with execvp");
                _exit(EXIT_FAILURE);
            }

            /*[>Releasing allocated memory<]*/
            freeCmdLines(pCmdLine);
        }
        else { 

            if(feedPipe(pipesfd,pCmdLine) != NULL) {
                close(0);
                pipeOut_dup = dup(feedPipe(pipesfd,pCmdLine)[0]);    /*[> [>duplicate the write-end of the pipe<]<]*/
                if (pipeOut_dup == -1) {
                    perror("pipeOut_dup");
                    exit(EXIT_FAILURE);
                }
            }
            
            if(sinkPipe(pipesfd,pCmdLine) != NULL) {
                close(1);
                pipeIn_dup = dup(sinkPipe(pipesfd,pCmdLine)[1]);    /*[> [>duplicate the write-end of the pipe<]<]*/
                if (pipeOut_dup == -1) {
                    perror("pipeOut_dup");
                    exit(EXIT_FAILURE);
                }
            }
            /*[>executing the program<]*/
            if(execvp(pCmdLine->arguments[0],pCmdLine->arguments) == -1) {
                perror("error with execvp");
                _exit(EXIT_FAILURE);
            }
            /*[>Releasing allocated memory<]*/
            freeCmdLines(pCmdLine);
        }
    }
    else {
        
        if(sinkPipe(pipesfd,pCmdLine) != NULL) {
            close(sinkPipe(pipesfd,pCmdLine)[1]);
        }

        if( pCmdLine->blocking != 0){
            waitpid(cpid,NULL,0);                          /*[>[ Wait for child #1 <]<]*/
        } else {
            waitpid(cpid,NULL,0);                          /*[>[ Wait for child #1 <]<]*/
        }
        pCmdLine = pCmdLine->next;
    }
    }
}

/*working with single line*/
void executeWithSinglePipe(cmdLine *pCmdLine){

    printf("in exe single pipe\n");
    
    printf("in exe with single pipe\n");
    int pipefd[2];
    pid_t cpid;
    pid_t cpid2;
    int fd_input,fd_output;
    int pipeOut_dup,pipeIn_dup;
    cmdLine *nextcommand = pCmdLine->next;

    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /*in child number 1*/
    if(!(cpid = fork())) {

        /*lets check if need to use the redirectInput*/
        if(pCmdLine->inputRedirect != NULL){
            close(0);
            fd_input = open(pCmdLine->inputRedirect,O_RDONLY, 0700);
            if(fd_input== -1){
                perror("input_fail");
                exit(EXIT_FAILURE);
            }
        }
        /*Handling redirectOutput*/
        if(pCmdLine->outputRedirect != NULL){
            close(1);
            fd_output = open(pCmdLine->outputRedirect, O_CREAT | O_WRONLY , 0700);
            if(fd_output == -1){
                perror("output_fail");
                exit(EXIT_FAILURE);
            }
            /*executing the program*/
            if(execvp(pCmdLine->arguments[0],pCmdLine->arguments) == -1) {
                perror("error with execvp");
                _exit(EXIT_FAILURE);
            }

            /*Releasing allocated memory*/
            freeCmdLines(pCmdLine);
        }
        else { 
            close(1);
            pipeOut_dup = dup(pipefd[1]);    /* [>duplicate the write-end of the pipe<]*/
            if (pipeOut_dup == -1) {
                perror("pipeOut_dup");
                exit(EXIT_FAILURE);
            }
            close(pipefd[1]);
            
            printf("executing cmd in first child  %s \n",pCmdLine->arguments[0]);

            /*executing the program*/
            if(execvp(pCmdLine->arguments[0],pCmdLine->arguments) == -1) {
                perror("error with execvp");
                _exit(EXIT_FAILURE);
            }

            /*Releasing allocated memory*/
            freeCmdLines(pCmdLine);
        }
    }
    else {

        /*---Terminal - Father Number 1----*/
        close(pipefd[1]);          /* [> Close unused write end <]*/

        cpid2 = fork();
        if (cpid2 == -1) {
            perror("fork2");
            exit(EXIT_FAILURE);
        }
        if (cpid2 == 0) { /*[>child # 2<] */  

            /*Handling redirectInput*/
        if(nextcommand->inputRedirect != NULL){
            close(0);
            fd_input = open(nextcommand->inputRedirect,O_RDONLY, 0700);
            if(fd_input== -1){
                perror("input_fail");
                exit(EXIT_FAILURE);
            }
        }
            /*Handling redirectOutput*/
            if(nextcommand->outputRedirect != NULL){
                close(1);
                fd_output = open(nextcommand->outputRedirect, O_CREAT | O_WRONLY | O_APPEND, 0700);
                if(fd_output == -1){
                    perror("output_fail");
                    exit(EXIT_FAILURE);
                }
        }
            close(0);                        /*  [> closing the standard output<]*/
            pipeIn_dup = dup(pipefd[0]);     /*[>duplicate the read-end of the pipe<]*/
            if (pipeOut_dup == -1) {
                perror("pipeOut_dup");
                exit(EXIT_FAILURE);
            }
            close(pipefd[0]);
            
            printf("executing cmd in seconde child  %s \n",nextcommand->arguments[0]);

            /*executing the program*/
            if(execvp(nextcommand->arguments[0],nextcommand->arguments) == -1) {
                perror("error with execvp child 2");
                _exit(EXIT_FAILURE);
        
                /*Releasing allocated memory*/
                freeCmdLines(pCmdLine);
            }
        } else { 
            /*[>---Father Number 2----<]*/
            close(pipefd[0]);       /*[> Close unused write end <]*/
            waitpid(cpid,NULL,0);      /*[ Wait for child #1 <]*/
            waitpid(cpid2,NULL,0);      /*[>[ Wait for child #2 <]<]*/
        }
    }
}
