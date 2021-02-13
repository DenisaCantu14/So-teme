#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>


void * inv (void * v) {
    int i,j=0;
    char *sir = v;
    int n = strlen(sir);
    char* result = (char*) malloc (n);
    for( i = n - 1; i >= 0; i --)
        result[j++] = sir[i];
    return result;
}

int main(int argc, char*argv[]) {


    char *sir = argv[1];
    pthread_t thr;
    if(pthread_create(&thr, NULL, inv, sir)) {
        perror(NULL);
        return errno;
    }
    void* result;
    if(pthread_join(thr, &result)) {
        perror(NULL);
        return errno;
    }
    char * r = result;
    printf("%s\n", r);
    return 0;
}
