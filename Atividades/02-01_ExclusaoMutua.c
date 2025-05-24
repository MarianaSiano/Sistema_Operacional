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
    return 0;
}