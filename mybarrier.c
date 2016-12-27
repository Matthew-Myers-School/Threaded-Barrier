#include <stdlib.h>
#include "mybarrier.h"


mybarrier_t * mybarrier_init(unsigned int count)
{
    mybarrier_t * barrier = malloc(sizeof(*barrier));
    
	if (NULL == barrier) {
        return NULL;
    }
    int ret = 0;
    ret = pthread_mutex_init(&barrier->mutex, NULL);
    pthread_mutex_lock(&(barrier->mutex));
    barrier->count = count;
    ret = pthread_cond_init(&barrier->cond, NULL);
    pthread_mutex_unlock(&(barrier->mutex));
	/* Add your implementation here */
    
    return barrier;	

}

int mybarrier_destroy(mybarrier_t * barrier)
{
    
	int ret = 0;
    if (NULL == barrier)
    {
        return -1;
    }
    pthread_mutex_lock(&barrier->mutex);
    while (barrier->count > 0)
    {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    }
    pthread_mutex_unlock(&barrier->mutex);
    free(barrier);
	/* Add your implementation here */
	
	return ret;
}

int mybarrier_wait(mybarrier_t * barrier)
{
    if (NULL == barrier)
    {
        return -1;
    }
    if (barrier->count < 0)
    {
        return -1;
    }
	int ret = 0;
    pthread_mutex_lock(&(barrier->mutex));
    barrier->count--;
    if (barrier->count == -1)
    {
        return -1;
    }
    if (barrier->count ==0)
    {
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);
        return 0;
    }

    while (barrier->count > 0)
    {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    }
    pthread_mutex_unlock(&(barrier->mutex));
	
	return ret;
}


