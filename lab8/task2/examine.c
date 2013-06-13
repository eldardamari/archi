#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/stat.h>
#include <sys/mman.h>


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

    header   = (Elf32_Ehdr *) map_start;
    sections = map_start + header->e_shoff;  

    /*Task0*/
    printf("\n ***Printig Section + Header *** \n");
    /* Printing Magic Numbers */
    printf("1)Magic #: %X %X %X\n", 
                header->e_ident[0], 
                header->e_ident[1], 
                header->e_ident[2]);
    
    /*Checking if file is an ELF format*/
    if (header->e_ident[0] != 0x7F
            || header->e_ident[1] != 0x45
            || header->e_ident[2] != 0x4C) {
        perror("Not an ELF file....aborting");
        exit(EXIT_FAILURE);
    }
    printf("2)Data Encoding     : %X\n"  ,header->e_ident[5]);
    printf("3)Entry Point       : 0x%x\n",header->e_entry);
    printf("4)Section Offset    : 0x%x\n",(Elf32_Off) header->e_shoff);
    printf("5)Section Entries   : %u\n"  ,(Elf32_Half) header->e_shnum);
    printf("6)Section Entry Size: %u\n"  ,(Elf32_Half) header->e_shentsize);
    printf("7)Program Offset    : 0x%x\n",(Elf32_Off)  header->e_phoff);
    printf("8)Program Entries   : %u\n"  ,(Elf32_Half) header->e_phnum);
    printf("9)Program Entry Size: %u\n"  ,(Elf32_Half) header->e_phentsize);

    /*Task1*/
    /*Printing Sections*/

    for(index=0; index < header->e_shnum ; index++) {
    printf("[%d]\t%s\t0x%X\t%d\t%d\n",
            index,
                (char*) map_start + 
                    sections[header->e_shstrndx].sh_offset +
                         sections[index].sh_name,
            sections[index].sh_offset,
            sections[index].sh_size,
            sections[index].sh_size);
    }
    
    /*Task2*/
    printf("\n ***Printig Symbolys *** \n");

    /*[>Printing Symbolys<]*/
    for (index=0; index < header->e_shnum; index++){

        if (sections[index].sh_type == SHT_SYMTAB || 
                sections[index].sh_type == SHT_DYNSYM) {

            symbol = (Elf32_Sym*) ((char*) map_start +  sections[index].sh_offset);
            symbol_count =  sections[index].sh_size / sizeof(Elf32_Sym);
                    
            name = (char*) map_start + 
                        sections[header->e_shstrndx].sh_offset + 
                        sections[index].sh_name;

            for(i=0 ; i < symbol_count ; i++) {

                    printf("[%d]\t%x\t0x%u\t%-10s\t%-30s\n",
                        i,
                        symbol[i].st_value,
                        symbol[i].st_shndx,
                        name,
                        (char*) map_start + 
                            sections[sections[index].sh_link].sh_offset + 
                            symbol[i].st_name);
            }
        }
    }
    munmap(map_start, fd_stat.st_size);
    close(fd);

    return EXIT_SUCCESS;
}
