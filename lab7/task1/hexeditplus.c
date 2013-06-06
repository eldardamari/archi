#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* forward declarations: */
void memDisaply(char* filename); 
void fileDisplay(char* filename);
void fileModify(char* filename);
void copyFromFile(char* filename);
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

    char sentence [100];
    unsigned int str[20];
    int size,i;
    unsigned char* ptr; 

    printf("Please enter <address> <length>\n");
    
    fflush(stdin);
    fgets(sentence,100,stdin);
    fgets(sentence,100,stdin);

        sscanf (sentence,"%x %d",str,&size);
        ptr = (unsigned char*)str;

        for (i=0 ; i< size ; i++) {
            printf ("%02x ",(unsigned int)ptr[i]);
        }

        /*reset values*/
        size = 0;
        i = 0;
        ptr = NULL;
}

void fileDisplay(char* filename) {
   
    char sentence [100];
    unsigned int str[20];
    int fd,fdl,size,i;
    unsigned char c; 
    
    printf("Please enter <location> <length>\n");


    fd = open(filename,O_RDONLY);
    if (fd < 0) {
        perror(filename);
        exit(0);
    }
    
    fflush(stdin);
    fgets(sentence,100,stdin);
    fgets(sentence,100,stdin);

    sscanf(sentence,"%x %d",str,&size);
    
    fdl = lseek(fd, *str ,SEEK_SET); 
    if (fdl == -1) {
        perror(filename);
        exit(0);
    }

        read(fd,&c,sizeof(c));
    
        for (i=0 ; i< size ; i++) {
        printf ("%02x ",c);
        read(fd,&c,sizeof(c));
    }

        /*reset values*/
        size = 0;
        i = 0;
        close(fd);
}

void fileModify(char* filename) {
    
    char sentence [100];
    unsigned int location[20];
    unsigned int val[20];
    int fd,fdl,size,i;
    unsigned char c; 

    printf("Please enter <location> <val>\n");
    fd = open(filename,O_RDWR);
    if (fd < 0) {
        perror(filename);
        exit(0);
    }
    
    fflush(stdin);
    fgets(sentence,100,stdin);
    fgets(sentence,100,stdin);

    sscanf(sentence,"%x %x",location,val);
    
    fdl = lseek(fd, *location ,SEEK_SET); 
    if (fdl == -1) {
        perror(filename);
        exit(0);
    }
        write(fd,&val,1);
    
        /*reset values*/
        size = 0;
        i = 0;
        close(fd);
}

void copyFromFile(char* filename) {
    
    char sentence [100];
    int slocation;
    int tlocation;
    char localfilename[20];
    int length;
    int fd,fd2,fdl,i;
    unsigned char c;

    printf("Please enter <source-file> <s-location> <t-location> <length>\n");
    
    fflush(stdin);
    fgets(sentence,100,stdin);
    fgets(sentence,100,stdin);
   
    sscanf(sentence,"%s %x %x %d",
            localfilename,
            &slocation,
            &tlocation,
            &length);
    /*open abc file*/
    
    fd = open(filename,O_RDWR);
    if (fd < 0) {
        perror(filename);
        exit(0);
    }

    /*open local file from user*/
    fd2 = open(localfilename,O_RDWR);
    if (fd < 0) {
        perror(localfilename);
        exit(0);
    }
    
    /*prepare file abc to be writen*/
    if( lseek(fd, tlocation ,SEEK_SET) == -1 ){ 
        perror(filename);
        exit(0);
    }
    
    /*reading from localfilename*/
    if( lseek(fd2, slocation ,SEEK_SET) == -1 ){ 
        perror(filename);
        exit(0);
    }
    
    for (i=0 ; i<length ; i++) {
        read(fd2,&c,sizeof(c));
        write(fd,&c,1);
    }
    
        close(fd);
        close(fd2);
}
void quit(char* filename){
    exit(0);
}

int main(int argc, char **argv){

    struct fun_desc menu[] = { 
        { "Mem Display",  memDisaply  }, 
        { "File Display", fileDisplay },
        { "File Modify", fileModify   },
        { "Copy From File", copyFromFile},
        { "Quit",         quit        } }; 

    int arraySize,fNum;
    int i = 0;
    int fd = 0;
    struct void_array iarray;

    if (argc != 2) {
        perror(argv[1]);
        exit(0);
    } else {
        /*fd = open(argv[1],O_RDWR); 
        if (fd == -1){
            perror(argv[1]);
            exit(0);*/
        } 

            while(1) 
            { 
                printf("\n\n--- File: %s ,choose action:---\n",argv[1]); 
                for(i=1 ; i <= 5 ; i++) 
                { 
                    printf("%d) %s \n",i,menu[i-1].name); 
                } 

                /*Reading user choose */
                scanf("%d",&fNum); 
                if(fNum>6 || fNum<0){ 
                    return 0; 
                } 

                printf("Option: %d\n\n",fNum); 
                menu[fNum-1].fun(argv[1]);
            }
    return 0; 
}
