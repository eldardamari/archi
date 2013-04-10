#include <stdio.h>
#include <stdlib.h>

typedef struct link link;

struct link {
    link *next;
    int data;
};
/*     Task1a     */
/*function delclerations*/
void list_print(link *list); 
int list_size(link *list); 
link *list_append(link *list, int data);
void list_free(link *list);  

/*     Task1b     */
/*function delclerations*/
int reduce(link *l, int (*f)(int, int), int iv);
int sum(int a, int b); 
int max(int a, int b); 

/*function*/

/* Return the number of elements in the list. */ 
int list_size(link *list) {

    int size = 0;

    if (list == NULL) {
        return size;
    } else {

        link *firstlink = list;

        while ((*list).next != NULL) {
            size++;
            list = (*list).next;
        }
            size++;
        list = firstlink;
        return size;
    }
}

/* Print the data of every link in list. Each data is followed by 
 * a newline character. */ 
void list_print(link *list){ 
    
    link *firstlink = list;
    
    while ((*list).next != NULL) {
        
        printf("%d\n",(*list).data);
        list = (*list).next;
    }
        printf("%d\n",(*list).data);
        list = firstlink;
}

 /* Add a new link with the given data to the end of the list and return a 
  * pointer to the list (i.e., the first link in the list). If list is null 
  * - create a new link and return a pointer to the link. */ 
link *list_append(link *list, int data) {

    if (list == NULL) {

        link *firstlink = (link*)calloc(1,sizeof(link));
        (*firstlink).next = NULL;
        (*firstlink).data = data;
        return firstlink;

    } else {

        link* firstlink = list;
        while ((*list).next != NULL) { /*while we gave a next link */

            list = (*list).next;
        }
       /* assigning new link and data to the end of the linked list */ 
        link *lastlink = (link*)calloc(1,sizeof(link));
        (*lastlink).next = NULL;
        (*lastlink).data = data;
        (*list).next = lastlink;

        return firstlink;
    }
}

/* Free the memory allocated by the list. */   
void list_free(link *list) {

    while ((*list).next != NULL) {
    
        link *templink = list;
        list = (*list).next;
        free (templink);
    }
    free (list);
}

/*     Task1b     */
/* Operates on the list values to collapse or combine those values into 
 * a single value, by applying the same computation to each value, starting 
 * from the initial value. */
int reduce(link *l, int (*f)(int, int), int iv) {

    if (l == NULL) {
        return iv;
    } else {

        if ((*l).next == NULL) { /* end of linked list*/
            return f(iv,(*l).data);
        } else {
            return f( reduce( ((*l).next), f, iv) , (*l).data);

        }
    }
}

/* Returns the sum of a and b */
int sum(int a, int b) {
    return a+b;
}

/* Returns the maximum of a and b */
int max(int a, int b) {

    if (a == b) {
        return a;
    }
    else if (a > b) {
        return a;
    } else {
        return b;
    }
}



int main(int argc, char **argv) {

    /* Task1a
    printf("Welcome: \n");

    link *list = 0;
    list = list_append(list, 1);
    list = list_append(list, 2);
    list = list_append(list, 3);
    printf("The list size is: %d\n", list_size(list));
    printf("The list content is:\n");
    list_print(list);
    list_free(list); */

    /*  Task1b */

    link *list = 0;
    list = list_append(list, 1);
    list = list_append(list, 2);
    list = list_append(list, 3);
    printf("The sum of all list values: %d\n", reduce(list,sum,0));
    printf("The max value of list links: %d\n", reduce(list,max,0));
    printf("the list content:\n");
    list_print(list);
    list_free(list);

    return 0;
}
