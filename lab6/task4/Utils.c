#ifndef UTILS
#define UTILS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "LineParser.h"
#include "Utils.h"

int **createPipes(int nPipes) {

    int **pipes;
    int i;

    /*allocating an array of pipes*/
    pipes = (int **)malloc(nPipes*sizeof(int));
    if(pipes == NULL){
        perror("Problem allocating array of pipes");
        exit(EXIT_FAILURE);
    }

    /*allocating memory for each pipe and assigning pipe to each*/
    for (i=0 ; i<nPipes ; i++) {
        pipes[i] = (int*)malloc(2*sizeof(int));
       if (pipe(pipes[i]) == -1) {
           perror("Error:= pipe(pipe[i]");
           exit(EXIT_FAILURE);
       }
    }
    return pipes;
}

void releasePipes(int **pipes, int nPipes) {

    int i;

    for (i=0 ; i < nPipes ; i++) {
        free(pipes[i]);
    }
    free(pipes);
}

int *feedPipe(int **pipes, cmdLine *pCmdLine) {

    int index = pCmdLine->idx;

    if (index == 0)
        return NULL;

    if (pipes[index-1] == NULL) {
        printf("**feedPipe** : no pipes avaliabe for chain number:%d , in pipes[index-1]\n",index);
    }
    else {
        return pipes[index-1];
    }
    return NULL;
}

int *sinkPipe(int **pipes, cmdLine *pCmdLine) {

    int index = pCmdLine->idx;

    if (pCmdLine->next == NULL)
        return NULL;

    if (pipes[index] == NULL) {
        printf("**sinkPipe** : no pipes avaliabe for chain number:%d , in pipes[index-1]\n",index);
    }
    else {
        return pipes[index];
    }
    return NULL;
}
#endif
