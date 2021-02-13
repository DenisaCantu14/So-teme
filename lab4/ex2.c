#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) 
{
	pid_t pid = fork();
	if(pid < 0)
		return errno;
	else 
		if (pid == 0)
		 {
			int value = atoi(argv[1]);
			printf("%d: ", value );
			while(value != 1)
			 {
				printf("%d ", value );
				if(value  % 2 == 0)
					value  = value  / 2;
				else
					value = 3*value  + 1;
			}

			printf("1\nChild %d finished\n",  getpid());
			exit(0);
		}
		else
		{
			wait(NULL);
		}
return 0;
}

