#include <stdio.h>
#include <stdlib.h>
 
/* forward declarations: */
void rec_map(int*, int, int (*f) (int));
int inc(int i); 
int dec(int i);
int iprt(int i);

struct fun_desc {
      char *name;
        int (*fun)(int);
};
struct int_array {
    int *array;
    int sz;
    void (*map) (struct int_array *, int (*f) (int));
};

void int_array_map(struct int_array *iarray, int (*f) (int)){
    rec_map(iarray->array,iarray->sz,f);
}
 
void initialize_int_array(struct int_array *iarray, int *array, int sz){
    int i;
    iarray->array = (int*)malloc(sz*sizeof(int)); 
    for(i=0 ; i < sz ; i++) {
        iarray->array[i] = array[i];
    }
   
    iarray->sz=sz;
    iarray->map =int_array_map;
}
 
/*  2.a functions here */
int inc(int i) {
    return i+1;
}
int dec(int i) {
    return i-1;
}
int iprt(int i){
    printf("%d\n",i);
    return i;
}
 
/*  2.b functions here */
void rec_map(int *array, int sz, int (*f) (int)){
    
    if (sz == 0){
        return;
    }
    else {
        array[sz-1] = f(array[sz-1]);
        rec_map(array,sz-1,f);
        return;
    }
}
 
int main(int argc, char **argv){

    /* task2a
     int i = 1;
    int j;
    printf("inc test: i: %d , after i is:%d\n",i,inc(i));
    printf("dec test: i: %d , after i is:%d\n",i,dec(i));
    printf("iprt test:\n");
    j = iprt(i);
    printf("return value is %d\n",j);*/
   
    
    
   /* 
    int a[] = {1,1,1};
    int i;
    
    for(i=0; i < 3 ; i++){
        printf("%d\n",a[i]);
    }
    
    rec_map(a,3,inc);
    
    for(i=0; i < 3 ; i++){
        printf("%d\n",a[i]);
    }
    
    return 0;
    {
    task2c
     
    int array[3] = {1,1,1};
    int i;
    struct int_array iarray;
    initialize_int_array(&iarray, array, 3);
    iarray.map(&iarray,dec);

    for(i=0; i < 3 ; i++){
    printf("%d\n",array[i]);
    }

    for(i=0; i < 3 ; i++){
    printf("%d\n",iarray.array[i]);
    }

*/
    /* task3 */
     
       struct fun_desc menu[] = { { "Inc", inc }, { "Dec", dec } , {"Iprt",iprt} }; 
       int arraySize,fNum;
       int i = 0;

       /* Empty array to fill up by the user */
        struct int_array iarray;

        printf("Please enter array size (0<size<=10): \n"); 
        scanf("%d",&arraySize); 
        int array[arraySize]; 
        for(i=0;i<arraySize;i++) 
        {    
            printf("Please enter array[%d]: \n",i); 
            scanf("%d",&(array[i])); 
        } 
        initialize_int_array(&iarray, array, arraySize); /* Initializing iarray with data*/
        while(1) 
        { 
            printf("Please choose a function\n"); 
            for(i=0;i<3;i++) 
            { 
                printf("%d) %s \n",i,menu[i].name); 
            } 
            scanf("%d",&fNum); 
            if(fNum>3 || fNum<0) 
            { 
                return 0; 
            } 
            printf("Option: %d\n",fNum); 
            iarray.map(&iarray,menu[fNum].fun); /* applying func on struct*/ 
            printf("DONE.\n"); 
        }
       
        
        return 0; 
}
