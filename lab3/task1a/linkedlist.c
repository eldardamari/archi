#include <stdio.h>
#include <stdlib.h>

typedef struct link link;

struct link {
    link *next;
    int data;
};

/*function delclerations*/
void list_print(link *list); 
int list_size(link *list); 
link *list_append(link *list, int data);
void list_free(link *list);  


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


int main(int argc, char **argv) {

    printf("Welcome: \n");

    link *list = 0;
    list = list_append(list, 1);
    list = list_append(list, 2);
    list = list_append(list, 3);
    printf("The list size is: %d\n", list_size(list));
    printf("The list content is:\n");
    list_print(list);
    list_free(list);
    return 0;
}
