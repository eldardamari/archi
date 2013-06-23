#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int is_pal(char *str) {

    unsigned int len = 0 ;
    char* count_string = str ;
    int index; 
    
    /*we can't use library functions, so we count manually*/
    while( (*count_string) != '\0') {
        count_string++; 
        len++;
    }
    
    /*iterating through string and comparing chars
        if not even return 0 = fail , return 1 = succsess*/
    for (index=0 ; index < len ; index++) {
        if (str[index] != str [len-1]) { 
            return 0;
        } 
        len--;
    }
    return 1;
}
/*Unused main function*/
int main(int argc,char* argv[]) {
    printf("check poly: %d \n",is_pal("1441"));
    return 0;
}
