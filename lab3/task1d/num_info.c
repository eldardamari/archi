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


/*     Task1c     */
/*function delclerations*/
int odd(int a);    
int gt5(int a);   
int square(int a);



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

/* returns a if a is an odd number, 0 otherwise */
int odd(int a) {

    if (a % 2 != 0) {
        return a;
    } else {
        return 0;
    }
}

/* returns a if a is greater than 5, 0 otherwise */
int gt5(int a) {

    if (a > 5) {
        return a;
    } else {
        return 0;
    }
}

/* returns the square of a */
int square(int a) {

    return (a*a);
}

/* returns a new allocated list with the same number of links as in the 
 * original list. The value of the i-th element in the returned list is the 
 * result of applying the unary-operation function on the value of the i-th 
 * element of the original list. */
link *map(link *l, int (*f)(int)) {

    link *newlist = 0;
    link *firstlinklist = l;

    while ((*l).next != NULL) {
        
        newlist = list_append(newlist, f((*l).data));
        l = (*l).next;
    }
    newlist = list_append(newlist, f((*l).data));
    l = firstlinklist;
    return newlist;
}



void read_ints (const char* file_name)
{
      FILE* file = fopen (file_name, "r");
        int i = 0;

          fscanf (file, "%d", &i);    
            while (!feof (file))
                    {  
                              printf ("%d ", i);
                                    fscanf (file, "%d", &i);      
                                        }
              fclose (file);        
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

    /*  Task1b 

    link *list = 0;
    list = list_append(list, 1);
    list = list_append(list, 2);
    list = list_append(list, 3);
    printf("The sum of all list values: %d\n", reduce(list,sum,0));
    printf("The max value of list links: %d\n", reduce(list,max,0));
    printf("the list content:\n");
    list_print(list);
    list_free(list);
    */
    
    /* task1c 
    link *list = 0;
    link *new_list = 0;
    int res = 0;

    list = list_append(list, 1);
    list = list_append(list, 3);
    list = list_append(list, 8);

    new_list = map(list,odd);
    res = reduce(new_list, max, 0);

    printf("The maximal odd number in the list is: %d\n", res);
    printf("new_list content is:\n");
    list_print(new_list);

    list_free(list);
    list_free(new_list);
    */

    /* Task1d */


    FILE* file = fopen (argv[1], "r");
    int i = 0;
    int numbers = 0;
    int flag = 0;
    link *list = 0;

    fscanf (file, "%d", &i);    
    while (!feof (file))
    {  
        if (flag == 0) {

            numbers += i;
            flag = 1;
        } else {

            numbers = abs(numbers +i);
            /* Creating a linked list */
            list = list_append(list,numbers);

            numbers = 0;
            flag =0;
        }
        fscanf (file, "%d", &i);      
    }

    /* size */

    printf("Size: %d\n",list_size(list));


    /* maximal number of all numbers in the list that are odd and greater 
     * than 5. */

    link *newoddlist = NULL;
    link *greatert5 = NULL;
    int res = 0;

    newoddlist = map(list,odd);
    greatert5 = map(newoddlist,gt5);
    res = reduce(greatert5,max,0);

    
    printf("Max(odd and greater thab 5): %d\n",res);

    /* The sum of all the sqaures on the list */


    link *newsqrtlist = NULL;
    res = 0;
    newsqrtlist = map(list,square);
    res = reduce(newsqrtlist,sum,0);
    printf("Sum(squares): %d\n",res);

    list_free(list);
    list_free(newoddlist);
    list_free(newsqrtlist);
    list_free(greatert5);

    fclose (file);        
    return 0;
}
