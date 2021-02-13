#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
       char* text = "Hello World!\n";
       write(1, text, strlen(text) );

return 0;
}
