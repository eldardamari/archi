int linkedlistsize;

typedef struct varset
{
    char * name;
    char *value;
    struct varset *next;	/* next cmdLine in chain */
} varset;

/*Fucntions declarations*/
void addLink(varset **head,char* name,char* value);
void setData(varset *head,char* name,char* value);
void findAndDestoryLink(varset* head,char *nametodel);
void printall(varset* head);
char *getName(varset *head,char * str);
void freeall(varset *head);
