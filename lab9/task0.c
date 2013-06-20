#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>

/*Funstions Declarations*/
int foreach_phdr(void *map_start, void (*func) (Elf32_Phdr*, int), int arg);
void print_headers(Elf32_Phdr* pHeader,int num);

/*Functions*/
int foreach_phdr(void *map_start, void (*func) (Elf32_Phdr*, int), int arg) {
    int index;

    Elf32_Ehdr *header   = (Elf32_Ehdr*) map_start;
    Elf32_Phdr *p_header = (Elf32_Phdr*) (map_start + header->e_phoff);

    for (index=0; i<header->e_phnum; i++) {
        func((Elf32_Phdr*) ( ((void*) p_header) +
                            index*header->e_phentsize ), arg);
    }
    return EXIT_SUCCESS;
}

void print_headers(Elf32_Phdr* pHeader,int num){
    printf("Program Header Number [%d], In address:0x%x\n",
                                num,
                                pHeader.p_vaddr);
}


int main(int argc, char *argv[]) {
    int fd;
    unsigned int index, i,
                 symbol_count;
    char *name;
    struct stat fd_stat;
    void *map_start;
    Elf32_Ehdr *header;
    Elf32_Shdr *sections;
    Elf32_Sym *symbol;

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

    /*Task0*/
    foreach_phdr(map_start,print_headers,fd);

    /**Task1**/
        /*Task1a*/

    }
}
