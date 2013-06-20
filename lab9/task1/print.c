#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

/*Funstions Declarations*/
int foreach_phdr(void *map_start, void (*func) (Elf32_Phdr*, int), int arg);
void print_headers(Elf32_Phdr* pHeader,int num);
void load_all_program_headers(Elf32_Phdr* pHeader,int num);
int startup(int argc, char **argv, void (*start)());

/*Functions*/
int foreach_phdr(void *map_start, void (*func) (Elf32_Phdr*, int), int arg) {
    int index;

    Elf32_Ehdr *header   = (Elf32_Ehdr*) map_start;
    Elf32_Phdr *program_h = (Elf32_Phdr*) (map_start + header->e_phoff);

    for( index=0 ; index<header->e_phnum ; index++) {
        func((Elf32_Phdr*) ( ((void*)program_h) +
                    index*header->e_phentsize),arg);   /*need to replace index with arg*/
    }
    return 0;
}

/*printing headers*/
void print_headers(Elf32_Phdr* pHeader,int num){
    printf("Program Header Number [%d], In address:0x%x\n",
                                num,
                                pHeader->p_vaddr);
}

/*Load all programs to VM*/
void load_all_program_headers(Elf32_Phdr* pHeader,int num){

    int premmission = 0;
    void* map;

    if(pHeader != NULL &&
       pHeader->p_type == PT_LOAD) {

    /*[>Check for Read premmission<]*/
    if ( pHeader->p_flags & PF_R ) {
        premmission = premmission | PROT_READ;
    } else {
        premmission = premmission | 0;
    }
    
    /*[>Check for Write premmission<]*/
    if ( pHeader->p_flags & PF_W ) {
        premmission = premmission | PROT_WRITE;
    } else {
        premmission = premmission | 0;
    }
    
    /*[>Check for Execute premmission<]*/
    if ( pHeader->p_flags & PF_X ) {
        premmission = premmission | PROT_EXEC;
    } else {
        premmission = premmission | 0;
    }
        map = mmap(pHeader->p_vaddr & 0xfffff000,
                   pHeader->p_memsz + (pHeader->p_vaddr & 0xfff), 
                   premmission,
                   MAP_PRIVATE | MAP_FIXED,
                   num,
                   pHeader->p_offset & 0xfffff000);

        if (map < 0) {
            perror("Unable to map program header");
            exit(0);
        }
    }
}

/*Task1a*/
void print_all_data(Elf32_Phdr* pHeader,int num){

    /*Printing the type of program header*/

    switch(pHeader->p_type) {

        case PT_NULL:
            printf("%-10s\t","NULL"); 
                break;
        
        case PT_LOAD:
            printf("%-10s\t","LOAD"); 
                break;
        
        case PT_DYNAMIC:
            printf("%-10s\t","DYNAMIC"); 
                break;
        case PT_INTERP:
            printf("%-10s\t","INTERP"); 
                break;
        
        case PT_NOTE:
            printf("%-10s\t","NOTE"); 
                break;

        case PT_SHLIB:
            printf("%-10s\t","SHLIB"); 
                break;

        case PT_PHDR:
            printf("%-10s\t","PHDR"); 
                break;

        case PT_LOPROC:
            printf("%-10s\t","LOPROC"); 
                break;

        case PT_HIPROC:
            printf("%-10s\t","HIPROC"); 
                break;
        
        case PT_TLS:
            printf("%-10s\t","TLS"); 
                break;

        case PT_LOOS:
            printf("%-10s\t","LOOS"); 
                break;
        
        case PT_LOSUNW:
            printf("%-10s\t","LOSUNW"); 
                break;
        
        case PT_SUNWSTACK:
            printf("%-10s\t","SUNWSTACK"); 
                break;
        case PT_GNU_EH_FRAME:
            printf("%-10s\t","GNU_EH_FRAME"); 
                break;
        case PT_GNU_STACK:
            printf("%-10s\t","GNU_STACK"); 
                break;
        case PT_GNU_RELRO:
            printf("%-10s\t","GNU_RELRO"); 
                break;
    }

    /*printing all data*/
    /*Addreess*/
    printf("0x08%-5x\t0x08%-5x\t0x08%-5x\t0x08%-5x\t0x08%-5x\t", 
            pHeader->p_offset,
                    pHeader->p_vaddr,
                            pHeader->p_paddr,
                                 pHeader->p_filesz,
                                        pHeader->p_memsz);

    /*printign flags*/
        if ( pHeader->p_flags & PF_R ) {
            printf("%s","R");
        } 
        else {
            printf("%s"," ");
        }
        if ( pHeader->p_flags & PF_W ) {
            printf("%s","W");
        } 
        else {
            printf("%s"," ");
        }
        if ( pHeader->p_flags & PF_X ) {
            printf("%s","X");
        } 
        else {
            printf("%s"," ");
        }
            
        printf("\t");

    /*printign allianment*/
            printf("0x%x\n",pHeader->p_align);
}


int main(int argc, char *argv[]) {
    int fd;
    struct stat fd_stat;
    void *map_start;

    if( (fd = open(argv[1], O_RDWR)) < 0 ) {
        perror("error in open");
        exit(-1);
    }

    if( fstat(fd, &fd_stat) != 0 ) {
        perror("stat failed");
        exit(-1);
    }

    if ( (map_start = mmap(0, 
                    fd_stat.st_size, 
                    PROT_READ | PROT_WRITE , 
                    MAP_SHARED, 
                    fd, 
                    0)) < 0 ) {
        perror("mmap failed");
        exit(-4);
    }

    foreach_phdr(map_start,load_all_program_headers,fd);

    /*Start Program*/
    int exe_argc = argc-1;
    char ** exe_argv = &argv[1];
    void* start_entry = ((Elf32_Ehdr*)map_start)->e_entry;

    startup(exe_argc,exe_argv,start_entry);
}
