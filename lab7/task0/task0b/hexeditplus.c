#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/* forward declarations: */
void memDisaply(char* filename); 
void fileDisplay(char* filename);
void quit(char* filename);

struct fun_desc {
    char *name;
    void (*fun)(char* filename);
};

struct void_array {
    int *array;
    int sz;
    void (*map) (struct void_array *, void (*f) (char* filename));
};

/*  Functions here */
void memDisaply(char* filename) {
    return;
}
void fileDisplay(char* filename) {
    return;
}
void quit(char* filename){
    exit(0);
}

int main(int argc, char **argv){

    struct fun_desc menu[] = { 
        { "Mem Display",  memDisaply  }, 
        { "File Display", fileDisplay },
        { "Quit",         quit        } }; 

    int arraySize,fNum;
    int i = 0;
    int fd = 0;
    struct void_array iarray;


    if (argc != 2) {
        perror(argv[1]);
        exit(0);
    } else {
        fd = open(argv[1],O_RDWR); 
        if (fd == -1){
            perror(argv[1]);
            exit(0);
        } else {

            while(1) 
            { 
                printf("\n--- File: %s ,choose action:---\n",argv[1]); 
                for(i=1 ; i <= 3 ; i++) 
                { 
                    printf("%d) %s \n",i,menu[i-1].name); 
                } 

                /*Reading user choose */
                scanf("%d",&fNum); 
                if(fNum>3 || fNum<0){ 
                    return 0; 
                } 

                printf("Option: %d\n\n",fNum); 
                menu[fNum-1].fun(argv[1]);
            }
        }
    }
    return 0; 
}
