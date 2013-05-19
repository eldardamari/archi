#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    int pipeOut_dup;
    int pipeIn_dup;
    pid_t cpid;
    pid_t cpid2;
    char buf;
 
    char* arguments[4];
    arguments[0] = "tail";
    arguments[1] = "-n";
    arguments[2] = "1";
    arguments[3] = NULL;
    
    char *arguments1[3];
    arguments1[0] = "ls";
    arguments1[1] = "-l";
    arguments1[1] = NULL;
    

    if (pipe(pipefd) == -1) {       /*Inizializing pipe with array pipefd*/
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork1");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {   

        close(1);                          /*[>[> closing the standard output<]<]*/
        pipeOut_dup = dup(pipefd[1]);    /* [>duplicate the write-end of the pipe<]*/
        if (pipeOut_dup == -1) {
            perror("pipeOut_dup");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
    
        /*executing the program*/
        if(strlen(arguments1[1])==0)
            arguments1[1] = 0;
        if(execvp(arguments1[0],arguments1) == -1) {
            perror("error with execvp child 1");
            _exit(EXIT_FAILURE);
        }
    } else {           
        /*---Terminal - Father Number 1----*/
        close(pipefd[1]);          /* [> Close unused write end <]*/

        cpid2 = fork();
        if (cpid2 == -1) {
            perror("fork2");
            exit(EXIT_FAILURE);
        }
        if (cpid2 == 0) { /*[>child # 2<] */  

            close(0);                        /*  [> closing the standard output<]*/
            pipeIn_dup = dup(pipefd[0]);     /*[>duplicate the read-end of the pipe<]*/
            if (pipeOut_dup == -1) {
                perror("pipeOut_dup");
                exit(EXIT_FAILURE);
            }
            close(pipefd[0]);

            /*[>executing the program<]*/
            if(strlen(arguments[1])==0)
                arguments[1] = 0;
            arguments[3] = NULL;
            if(execvp(arguments[0],arguments) == -1) {
                perror("error with execvp child 2");
                _exit(EXIT_FAILURE);
            }
        } else { 
            /*[>---Father Number 2----<]*/
            close(pipefd[0]);       /*[> Close unused write end <]*/
            waitpid(cpid,NULL,0);      /*[ Wait for child #1 <]*/
            waitpid(cpid2,NULL,0);      /*[>[ Wait for child #2 <]<]*/
        }
    }
}
