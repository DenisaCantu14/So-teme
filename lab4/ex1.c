#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
int main()
{
        pid_t pid  = fork();
        if (pid < 0 )
                return errno;
        else if ( pid == 0)
                {
                        char * argv [] = {"ls", NULL};
                        execve("/bin/ls", argv, NULL);
                }
        else
        {
                printf("My PID = %d, Child PID =  %d\n", getpid(), pid);
                wait(NULL);
        }

        printf("Child %d finished!\n", pid);
        return 0;
}
