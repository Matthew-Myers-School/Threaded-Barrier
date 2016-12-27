//
//  main.cpp
//  
//
//  Created by Matthew Myers on 12/11/16.
//
//

#include <stdio.h>
#include <pthread.h>
#include "mybarrier.h"
#define SZ 100

struct threadA{
    mybarrier_t * b;
    int ID;
};

void * test(void * theArgs)
{
    struct threadA* a;
    a = theArgs;
    mybarrier_wait( a->b);
    printf("DONE WITH WAIT: TID: %d\n", a->ID);
    pthread_exit(0);
}
int main(){
    pthread_t threads[SZ];
    struct threadA threadArgs[SZ];
    mybarrier_t* bar;
    bar = mybarrier_init(SZ);
    for (int i = 0; i < SZ; i++)
    {
        threadArgs[i].b = bar;
        threadArgs[i].ID = i;
        pthread_create(&threads[i],NULL,&test,&threadArgs[i]);
        
    }
    for (int i = 0; i < SZ; i++)
    {
        pthread_join(threads[i], NULL);
    }
    mybarrier_destroy(bar);
    //sleep(1);
}
