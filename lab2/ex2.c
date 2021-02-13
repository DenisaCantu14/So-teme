#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main( int argc,  char* argv[])
{
	if( argc != 3)
	{	
		printf("Numarul de argumente  nu este corect\n");
	}
	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_WRONLY | O_CREAT);

	if(fd1 < 0)
	{
		perror("Eroare dechidere fisier de intrare!\n");
		return errno;
	}

	
        if (fd2 < 0)
               {
                 perror("Eroare deschidere fisier de iesire!");
		 return errno;
                }

	char txt[100];
	int r, w;
	while(r = read (fd1, &txt, 1)>0)
	{

		if (r != write(fd2, &txt, 1))
		{
			perror("read buf");
			return errno;
		}
	}
 
    	if (r < 0)
        {
                perror("write buf");
                return errno;
        }
	else
	{
		write(1,"Continutul fisierului a fost copiat cu succes", 46);
}

	close(fd1);
	close(fd2);
return 0;
}
