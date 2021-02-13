
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx; 

int decrease_count(int count) 
{ 
	pthread_mutex_lock(&mtx);
	if (available_resources<count) 
		{ 
			pthread_mutex_unlock(&mtx); 
			return -1;
		}
	else 
		available_resources -= count ;
	printf("Get %d resources, remaining %d resources\n",count,available_resources);
	pthread_mutex_unlock(&mtx);
	return 0; 
}

int increase_count(int count) 
{ 
	pthread_mutex_lock(&mtx);
	available_resources += count ;
	printf("Release %d resources, remaining %d resources\n",count,available_resources);
	pthread_mutex_unlock(&mtx);
	return 0; 
}

void *f(void *k)
{
	int n =*(int*) k;
	decrease_count(n);
	increase_count(n); 
	return NULL;
}

int main()
{
	if (pthread_mutex_init(&mtx, NULL)) 
	{ 
	      perror (NULL); 
	      return errno ; 
	}
	pthread_t t[20];
	void  *result;
	for(int i = 0; i < 10; i++)
	{
	   int *p = (int *)malloc(1);
	   *p = i % MAX_RESOURCES + 1;
	  
	   if(pthread_create(&t[i], NULL, f, p)) 
		{
       		     perror(NULL);
        	     return errno;
    		}
	  if(pthread_join(t[i], &result)) 
		{
        	     perror(NULL);
        	     return errno;
    		}
	}

	pthread_mutex_destroy(&mtx);
	return 0;
}

