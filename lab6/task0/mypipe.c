#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    if (argc >= 2) {
        fprintf(stderr, "Too many arguments \n");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1) {       /*Inizializing pipe with array pipefd*/
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {    /* Child reads from pipe */

        close(pipefd[0]);                        /* Close unused read end */
        write(pipefd[1], "Hello World\n", 12);
        close(pipefd[1]);                       /* Reader will see EOF */
        printf("sending to father..n");
        _exit(EXIT_SUCCESS);
    } else {            /* Parent writes argv[1] to pipe */
        close(pipefd[1]);                        /* Close unused read end */
        wait(NULL);                              /* Wait for child */
       
        printf("rceiving from my dear child!!\n");
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        exit(EXIT_SUCCESS);
    }
}
