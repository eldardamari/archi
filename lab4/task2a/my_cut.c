#include "util.h"

#define DT_REG 8   
#define O_DIRECTORY 00200000 

#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_LSEEK 19
#define SYS_EXIT 1
#define SYS_GETDENTS 141

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

    int fd, nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    int bpos;
    char d_type;
    int flag = 0;

    if (argc == 2) 
        flag =1 ;
    fd = system_call(SYS_OPEN,".",0);
    if (fd <0)
        system_call(SYS_EXIT,0x55);

    for ( ; ; ) {

        nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
        if (nread < 0)
            system_call(SYS_EXIT,0x55);

        if (nread == 0)
            break;

        for (bpos = 0; bpos < nread;) {

            d = (struct linux_dirent *) (buf + bpos);


            /* TODO - need to fix */
                if (strncmp(d->d_name, argv[2],strlen(argv[2])) != 0){

                    system_call(SYS_WRITE,STDOUT,d->d_name,strlen(d->d_name));
                    system_call(SYS_WRITE,STDOUT,"\n",1);
                    bpos += d->d_reclen;
                } 
            else {

                    system_call(SYS_WRITE,STDOUT,d->d_name,strlen(d->d_name));
                    system_call(SYS_WRITE,STDOUT,"\n",1);
                    bpos += d->d_reclen;

                }
            

            }

        }
    }
