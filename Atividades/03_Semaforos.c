#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <process.h>
#include <pthread.h>
#include <semaphore.h>
//#include <sys/wait.h>

//Atividade 3 - Semáforos (Produtor-Consumidor)
#define TAM 5
int buffer[TAM];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *produtor(void *arg)
{
    for(int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = i;
        in = (in + 1) % TAM;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumidor(void *arg)
{
    for(int i = 1; i <= 10; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int valor = buffer[out];
        out = (out + 1) % TAM;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Consumidor: %d\n", valor);
    }
    return NULL;
}

int main()
{
    return 0;
}