#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NTHRS 3

sem_t sem;
pthread_mutex_t mtx;
int S=0;
void * barrier_point()
{
    pthread_mutex_lock(&mtx);
    S++;
    pthread_mutex_unlock(&mtx);
    if(S<=NTHRS)
    {
        for(int i = 0; i < S; i++)
            sem_post(&sem);



    }
    else {
        if (sem_wait(&sem)) {
            perror(NULL);
            return errno;
        }
    }
}

void * f (void *v)
{
    int *tid = (int *)v;
    printf("%d reached the barrier \n",*tid);
    barrier_point();
    int value = (int *)v;
    printf("%d: ", value );
    while(value != 1)
    {
        printf("%d ", value );
        if(value  % 2 == 0)
            value  = value  / 2;
        else
            value  = 3 * value  + 1;
    }
    printf("1\n");

}

int main(int argc, char* argv[]) 
{
    pthread_t tid[7];
    if(sem_init (&sem, 0 ,S))
    {
        perror(NULL);
        return errno;
    }
    if(pthread_mutex_init(&mtx,NULL))
    {
        perror(NULL);
        return errno;
    }
	//printf("Starting Parent %d\n", getpid());
	for(int i = 1; i <= argc; i++) {
        int *nr = argv[i];
        if (pthread_create(&tid[i], NULL, f, nr)) {
            perror(NULL);
            return errno;
        }
        int *result;
        for (int i = 1; i <= argc; i++) {
            if (pthread_join(tid[i], &result)) {
                perror(NULL);
                return errno;
            }
        }
        sem_destroy(&sem);
        pthread_mutex_destroy(&mtx);
        return 0;
    }



				int value = atoi(argv[i]);
				printf("%d: ", value );
				while(value != 1)
				 {
					printf("%d ", value );
					if(value  % 2 == 0)
						value  = value  / 2;
					else
						value  = 3 * value  + 1;
				}
				printf("1\nDone Parent %d Me %d\n",  getppid(), getpid());
				exit(0);
			}
			else
			{
                		wait(NULL);
			       
			}
	}

/*	for(i = 1; i <= argc; i++)
		wait(NULL);*/
	printf("Done Parent %d Me %d\n", getppid(), getpid());

	return 0;
}
