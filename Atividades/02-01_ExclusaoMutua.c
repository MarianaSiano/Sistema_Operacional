#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <process.h>
#include <pthread.h>
//#include <sys/wait.h>

//Atividade 2 - Exclusão Mútua
//2.1 - Incremento com e sem mutex
int contador = 0;
pthread_mutex_t lock;

void *incrementar(void *arg)
{
    for(int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&lock);
        contador++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t threads[10];
    pthread_mutex_init(&lock, NULL);

    for(int i = 0; i < 10; i++)
        pthread_create(&threads[i], NULL, incrementar, NULL);

    for(int i = 0; i < 10; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);
    printf("Valor final do contador: %d\n", contador);
    return 0;
}