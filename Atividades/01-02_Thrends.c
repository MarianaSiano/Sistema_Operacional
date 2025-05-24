#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <process.h>
#include <pthread.h>
//#include <sys/wait.h>

//Atividade 1.2 - Criar Cinco Threads
void *func(void *arg)
{
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main()
{
    pthread_t threads[5];

    for(int i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, func, NULL);

    for(int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);

    return 0;
}