#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int a[5][4];
int b[4][5];

struct pair
{
   int l, c;
};

void * prod(void *args)
{
	struct pair *p = args;
	int *v = (int *)malloc(sizeof(int));
	for(int nr = 1; nr <= 4; nr++)
		(*v) += a[p -> l][nr] * b[nr][p -> c];
 	return v;
}

int main()
{
	pthread_t tid[17];
	int v[5][5];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 3; j++)
			a[i][j] = i;

	for (int i = 1; i <= 3; i++)
		for(int j = 1; j <= 4; j++)
			b[i][j] = j;

	int loc  = 1;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
		{
			struct pair *p1 = (struct pair*) malloc(sizeof(struct pair));
			p1 -> l = i; 
			p1 -> c = j;	
			if  (pthread_create (&tid[loc], NULL, prod, p1 ))
			{
				perror (NULL) ;
				return   errno;	
			}	
			loc++;
		}

	loc = 1;
	int *result;
	for (int i = 1; i <= 4; i++)	
		for (int j = 1; j <= 4; j++)
		{
			if (pthread_join (tid[loc], &result))
			{
				perror (NULL) ;
                        	return   errno; 
                        } 
			v[i][j] = *result;
			loc++;
		}
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
			printf ("%d ", v[i][j]);
		printf ("\n");
	}

	return 0;
}
