#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void splitLineByDelimiter();
void splitLineByNumber();
void readFromFile();

int main( int argc , char *argv[]) {

    if(argc == 1 ) {

        splitLineByDelimiter('s');
        return 0;
    }
    if(argc == 3 ) {

        if (strcmp(argv[1],"-d")==0) {

		// Comma delimiter
		if (strcmp(argv[2],"C")==0) {
			splitLineByDelimiter(',');
            		return 0;
		}
		// White Space delimiter
		else if (strcmp(argv[2],"W")==0) {
			splitLineByDelimiter(',');
            		return 0;
		}
		// Number Delimiter
		splitByNumebr();
		return 0;
	}
	else if (strcmp(argv[1],"-i")==0) {

		readFromFile();
		return 0;
		}

	}
	else if (argc >= 4) {

	if (strcmp(argv[1],"-d")==0) {
		
		if (strcmp(argv[2],"C")==0) {
			splitLineByDelimiterToFile(',');
            		return 0;
		}
		// White Space delimiter
		else if (strcmp(argv[2],"W")==0) {
			splitLineByDelimiterToFile('s');
            		return 0;
		}
		// Number Delimiter
		splitByNumebr();
		return 0;
		
	}

	}
}


void splitLineByDelimiter(char delimiter) {
    
    int c;

	if (delimtier == 's') {
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
	}
	else if ( delimter == ',') {

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
	}
}

void splitLineByNumber() {

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
}


void readFromFile() {

        FILE *file;

        file = fopen(argv[4],"r");


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
	fclose(file);
}

void writeToFile(char* fileName, char delimiter) {

        FILE *file;

        file = fopen(fileName,"w");


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
	fclose(file);
}


void splitLineByDelimiterToFile(char delimiter) {

	int numOfFiles = argv - 3;
	char *files[3];
	int i;
	int files = 3;
	int c;
	char *str;
	size_t len;

	for(i = 0; i < numOfFiles ; i++ ) {
		
		files[i] = argv[files];	
		files++:
	}


	// TODO Stoped here!!!!!! - 

        while ( c != EOF ) {
	
		for ( mod = 0 ; c != EOF ; mod ++) {

	            c = fgetc(stdin);
	            if (isspace(c)) {
	                c='\n';
	                fputc(c, stdout);
        	    }
	            else {
        	        if (c != EOF ) {
	                    fputc (c, files[mod]);
	                }
	            }

			mod++;
			if (mod == numOfFiles) {
			mod = 0;
			}
		}
	}
	if (delimtier == 's') {
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
		
		for (mod = 0 ; c != EOF ; ) {

			writeToFile(file[mod],delimiter);

		}


	}

	
}

void writeToFiles(char[3] files, char delimiter) {


	




}	
	





}
