#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main( int argc , char *argv[]) {

    int c;

    if(argc == 1 ) {

        while ( c != EOF ) {
            c = fgetc(stdin);
            if (isspace(c)) {
                c='\n';
                fputc(c, stdout);
            }
            else {

                if (c != EOF ) {
                    fputc (c, stdout);
                }
            }
        }
        return 0;
    }
    if(argc == 3 ) {

        if (strcmp(argv[1],"-d")==0 &&
                strcmp(argv[2],"C")==0) {

            while ( c != EOF ) {
                c = fgetc(stdin);
                if ( c == ',') {
                    c='\n';
                    fputc(c, stdout);
                }
                else {

                    if (c != EOF ) {
                        fputc (c, stdout);
                    }
                }
            }
            return 0;
        } else {

    int number = atoi(argv[2]);
    int j;
            while ( c != EOF ) {

                for (j=1 ; j <= number  && c != EOF; j++) {

                    c = fgetc(stdin);

                    if (j != number) {
                        if (c != EOF ) {
                            fputc (c, stdout);
                        }
                    } else {
                        c='\n';
                        if (c != EOF ) {
                            fputc (c, stdout);
                        }
                    }
                }
            }
            return 0;
        }
    }
    if (argc == 5) {

        FILE *file;

        file = fopen(argv[4],"r");

        if (strcmp(argv[1],"-d")==0 &&
                strcmp(argv[2],"C")==0) {

            while ( c != EOF ) {
                c = fgetc(file);
                if ( c == ',') {
                    c='\n';
                    fputc(c, stdout);
                }
                else {

                    if (c != EOF ) {
                        fputc (c, stdout);
                    }
                }
            }
            return 0;
        } 
        else {
            if (strcmp(argv[1],"-d")==0 &&
                    strcmp(argv[2],"W")==0) {
        
                while ( c != EOF ) {
                    c = fgetc(file);
                    if (isspace(c)) {
                        c='\n';
                        fputc(c, stdout);
                    }
                    else {

                        if (c != EOF ) {
                            fputc (c, stdout);
                        }
                    }
                }
                return 0;
            } else {

    int number = atoi(argv[2]);
    int j;
            while ( c != EOF ) {

                for (j=1 ; j <= number  && c != EOF; j++) {

                    c = fgetc(file);

                    if (j != number) {
                        if (c != EOF ) {
                            fputc (c, stdout);
                        }
                    } else {
                        c='\n';
                        if (c != EOF ) {
                            fputc (c, stdout);
                        }
                    }
                }
            }
            return 0;
        }

        fclose(file);

    }
    return 0;
}
}
