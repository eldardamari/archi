#include "util.h"

#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_LSEEK 19
#define SYS_EXIT 1

#define STDOUT 1
#define STDIN 0
int printsys(int status,int fd);

int printsys(int status, int fd) {
    
    char* buf[1]; /* buffer for reading characters */
    int f_read = 1;
    char* str;
    int i = 0;

    if (status == 0) {

        while (f_read > 0) {

            f_read = system_call(SYS_READ,fd,buf,1);
            if(f_read <= 0)
                return 0;

            if( i%2 == 0) { 
                system_call(SYS_WRITE,STDOUT,buf,1);
            }
            i+=1;
        }
    } else

        if (status == 1) {

        while (f_read > 0) {

            f_read = system_call(SYS_READ,fd,buf,1);
            if(f_read <= 0)
                return 0;

            if( i%2 == 1) { 
                system_call(SYS_WRITE,STDOUT,buf,1);
            }
            i+=1;
        }
        } else if (status == 2) {

            while (f_read > 0) {
                f_read = system_call(SYS_READ,fd,buf,1);
                if(f_read <= 0)
                    return 0;

                system_call(SYS_WRITE,STDOUT,buf,1);
            }
        }
}

int main (int argc , char* argv[], char* envp[])
{

    int fd;
    int fd1 = 0;
    int fd2 = 0;
    int fd3 = 0;
    int files[3] = {fd1,fd2,fd3};
    int i;
    int j = 0;
    if (argc < 2) 
    {
        system_call(SYS_WRITE,STDOUT,"Not enough arguments \n", 22);
        system_call(SYS_EXIT,0x55);
    }

    /* Task1a */
    fd = STDIN;


    if (argc > 2) { 

        i = 2;
         
        for( ; i < argc ; i++) {

            files[j] = system_call(SYS_OPEN,argv[i],0); /* open file from first 2nd argument to read only */
            if (files[j] < 0)
            {
                system_call(SYS_WRITE,STDOUT,"fail to open file \n",19);
                system_call(SYS_EXIT,0x55);
            }

            /* parsing the argumens, how to read data */
            if (strcmp(argv[1],"-o") == 0)
                printsys(0,files[j]);

            else if (strcmp(argv[1],"-e") == 0)
                printsys(1,files[j]);

            else if (strcmp(argv[1],"-n") == 0)
                printsys(2,files[j]);
        }
        return 0;
    }
            
    /* parsing the argumens, how to read data */
    if (strcmp(argv[1],"-o") == 0)
        printsys(0,fd);

    else if (strcmp(argv[1],"-e") == 0)
        printsys(1,fd);

    else if (strcmp(argv[1],"-n") == 0)
        printsys(2,fd);
}
