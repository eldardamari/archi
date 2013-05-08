#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

/*Add a link to the linked list*/
void addLink(varset **head,char* name,char* value){

    int i;
    varset *temp;
    varset *temp_next;
    varset *temp_back;
 
    /*Setting a new head*/
    if(linkedlistsize == 0){
        (*head) = (varset*)malloc(sizeof(varset));

            if(*head == NULL){
            }
        setData(*head,name,value);
        linkedlistsize++;
    }
    else 
    {
        temp = (*head);
       for(i = 0; i < linkedlistsize ; i++){
           temp_back = (*head);
           temp_next = (*head)->next;
           (*head) = temp_next;
        }
       (*head) = (varset*)malloc(sizeof(varset));
       temp_back->next = (*head);
       setData((*head),name,value);

       linkedlistsize++;
       (*head) = temp;
    }
}

/*set data into a the current link*/
void setData(varset *head,char* name,char* value){

    /*setting name*/
    head->name = (char*)malloc((strlen(name))+1);
    strcpy(head->name,name);
    
    /*setting value*/
    head->value = (char*)malloc((strlen(value))+1);
    strcpy(head->value,value);

    /*next to be NULL*/
    head->next = 0;

}

/*search linked list from chain*/
void findAndDestoryLink(varset* head,char *nametodel){

    int i;
    varset* prev_varset = NULL;
    prev_varset = head;

    if(linkedlistsize != 0){

        for(i = 0; i < linkedlistsize ; i++){

            if(strcmp(head->name,nametodel) == 0){
                prev_varset->next = head->next;
                free(head);
                linkedlistsize--;
                return;
            }
            prev_varset = head;
            head = head->next;
        }
    }
    printf("Sorry mate, but the variable: %s cannot be found\n",nametodel);
    return;
}

/*print all the variables and values*/
void printall(varset* head){

    int i;
    for( i = 0 ; i < linkedlistsize ; i++ ){
        printf("var: %s = %s\n",head->name,head->value); 
        head = head->next;
    }
}

char *getName(varset *head,char * str){

    int i;
    varset* prev_varset = NULL;
    char* temp_tostr = NULL;
    prev_varset = head;

    if(linkedlistsize != 0){

        for(i = 0; i < linkedlistsize ; i++){
    
            if(strcmp(head->name,str) == 0){
               temp_tostr = head->value; 
               head = prev_varset;
                return temp_tostr; 
            }
            head = head->next;
        }
    }
    printf("Sorry mate, but the variable: cannot be found\n");
    return NULL;
}

//TODO!!!!
/* free all memory */
void freeall(){

}
#endif
