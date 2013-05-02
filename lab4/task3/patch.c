#include "util.h"


#define DT_REG 8   
#define O_DIRECTORY 00200000 

#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_LSEEK 19
#define SYS_EXIT 1
#define SYS_GETDENTS 141
#define SYS_CLOSE 6

#define BUF_SIZE 1024
#define STDOUT 1
#define STDIN 0

struct linux_dirent {                                                      
    unsigned long  d_ino;                 /* inode number */               
    unsigned long  d_off;                /* offset to next dirent */       
    unsigned short d_reclen;    /* length of this dirent */                
    char d_name[];   /* filename (null-terminated) */                      
};  


int main (int argc , char* argv[], char* envp[]) {

    int fd_greeting = 0;
    int fd_greeting_R = 0;
    int pos_greeting = 0;
    int i = 5;
    int size_newname = 0;

    /* Opening greeting file to into write mode */
    fd_greeting = system_call(SYS_OPEN,"greeting",2);
        if (fd_greeting < 0)
            system_call(SYS_EXIT,0x55);
    
        pos_greeting = system_call(SYS_LSEEK,fd_greeting,1360,1);

            fd_greeting_R = 
                system_call(SYS_WRITE,fd_greeting,argv[1],
                        strlen(argv[1])+1);

        return 0;
}
