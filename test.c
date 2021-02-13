#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
#define NTHRS 5
 
sem_t sem;
pthread_mutex_t mtx;
int resurse=3;
 
void barrier_point(int n)
{
        pthread_mutex_lock(&mtx);
        resurse --;
        pthread_mutex_unlock(&mtx);
        if(sem_wait(&sem))
                {
                        perror(NULL);
                        return errno;
                }
	else { 
		    while(n != 1)
			{    
                     	   printf("%d ",n);
                       	   if( n % 2 == 0)
				 n = n / 2;
                	   else
				 n = 3 * n + 1;
                         }
                     printf("%d\n", n);
		     sem_post(&sem);
	             pthread_mutex_lock(&mtx);
        	     resurse++;
       		     pthread_mutex_unlock(&mtx);	
		}
         
}
 

void * f(void *v)
{
        int *nr=(int *)v;
        barrier_point(nr);	
	
}


 
int main(int argc, char* argv[])
{
        pthread_t thr[5];
        int i;
        if(sem_init(&sem,0,3))
        {
                perror(NULL);
                return errno;
        }
        if(pthread_mutex_init(&mtx,NULL))
        {
                perror(NULL);
                return errno;
        }
        for(i=0;i<NTHRS;i++)
        {
		
		int p;
                p = atoi(argv[i+1]);
                if(pthread_create(&thr[i],NULL,f,p))
                        {
                                perror(NULL);
                                return errno;
                        }
        }
        void  *rezultat=(void *)malloc(1);
                for(i=0;i<NTHRS;i++)
                {
                        if(pthread_join(thr[i],&rezultat))
                        {
                                perror(NULL);
                                return errno;
                        }
                }
 
        return 0;
}
