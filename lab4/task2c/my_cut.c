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

    int fd, nread;
    int fd_app = 0;
    int app_check = 0;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    int bpos;
    char d_type, c;
    int flag = 0;
    int prefix = 0;
    int append = 0;
    int fd_app_source = 0;

    system_call(SYS_WRITE,STDOUT,"Flame2 Strikes Again! \n",23);

    if (argc == 3){ 
        if(strcmp("-p",argv[1]) == 0) {
            prefix = 1;
        } else
            if(strcmp("-a",argv[1]) == 0) {
                append = 1;
            }
    }

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
            d_type = *(buf + bpos + d->d_reclen - 1);

            if ( d_type == DT_REG ) { /* Checking if file is regular */
                if (prefix == 1) {

                    if (strncmp(d->d_name, argv[2],strlen(argv[2])) == 0){

                        system_call(SYS_WRITE,STDOUT,d->d_name,strlen(d->d_name));
                        system_call(SYS_WRITE,STDOUT,"fuck \n",6);
                    } 
                }
                else if (append == 1) {

                    if (strncmp(d->d_name, argv[2],strlen(argv[2])) == 0){
                        
                        system_call(SYS_WRITE,STDOUT,d->d_name,strlen(d->d_name));

                        fd_app_source = 
                            system_call(SYS_OPEN,"run",0,1);

                        /*First Lets open the file matched with append */
                        fd_app =  system_call(SYS_OPEN,d->d_name,1,1);
                        if (fd_app > 0)
                            system_call(SYS_WRITE,STDOUT,"file opened \n",13);
                        system_call(SYS_LSEEK,fd_app,1,2);

                        //TODO!!!! need to append binary file "run" !! 
                        while (system_call(SYS_READ,fd_app_source,c,1)){
                            app_check = 
                                system_call(SYS_WRITE,fd_app,c,strlen(c));
                            if (app_check > 0)
                                system_call(SYS_WRITE,STDOUT,"appended \n",13);
                        }
                        
                        system_call(SYS_LSEEK,fd_app_source,1,0);

                        /*Writing into selected file - appending*/
                        /* still need to append binary file */

                        system_call(SYS_CLOSE,fd_app);
                        }
                    }
                }
                bpos += d->d_reclen;
            }
        }
    system_call(SYS_CLOSE,fd_app_source);
}
