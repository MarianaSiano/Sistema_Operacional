#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <windows.h>
// #include <process.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>

void *func(void *arg)
{
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

//Atividade 2.1 - Incremento com mutex
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

//Atividade 5.5 - Jantar dos Filósofos
#define NUM_FILOSOFOS 5
sem_t garfo[NUM_FILOSOFOS];

void *filosofo(void *arg) 
{
    int id = *(int*) arg;

    while(1) {
        printf("Filosofo %d está pensando...\n", id);
        sleep(rand() % 3 + 1);

        if(id % 2 == 0) {
            sem_wait(&garfo[(id + 1) % NUM_FILOSOFOS]); //NUM_FILOSOFOS 5
            sem_wait(&garfo[id]);
        } 

        else {
            sem_wait(&garfo[id]);
            sem_wait(&garfo[(id + 1) % NUM_FILOSOFOS]);
        }

        printf("Filosofo %d está comendo...\n", id);
        sleep(rand() % 2 + 1);

        sem_post(&garfo[id]);
        sem_post(&garfo[(id + 1) % NUM_FILOSOFOS]);

        printf("Filosofo %d terminou de comer.\n", id);
    }
    return NULL;
}

int main()
{
    int opcao;
    do {
        printf("\n======================= MENU =======================\n");
        printf("1. Atividade 1.1 - Processos\n");
        printf("2. Atividade 1.2 - Threads\n");
        printf("3. Atividade 2.1 - Mutex\n");
        printf("4. Atividade 3 - Produtor/Consumidor\n");
        printf("5. Atividade 5.5 - Jantar dos Filosofos (Deadlock)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao => ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1: {
            for(int i = 0; i < 3; i++) {
                pid_t pid = fork();

                if(pid < 0) {
                    perror("Erro ao criar processo filho");
                    exit(1);
                }

                else if(pid == 0) {
                    printf("Processo filho (PID: %d), PID do pai: %d\n", getpid(), getppid());
                    exit(0);
                }
            }

            for(int i = 0; i < 3; i++)
                wait(NULL);

            printf("Processo pai finalizado\n");
            break;
        }

        case 2: {
            pthread_t threads[5];

            for(int i = 0; i < 5; i++)
                pthread_create(&threads[i], NULL, func, NULL);

            for(int i = 0; i < 5; i++)
                pthread_join(threads[i], NULL);

            break;
        }

        case 3: {
            pthread_t threads[10];
            pthread_mutex_init(&lock, NULL);

            for(int i = 0; i < 10; i++)
                pthread_create(&threads[i], NULL, incrementar, NULL);

            for(int i = 0; i < 10; i++)
                pthread_join(threads[i], NULL);

            pthread_mutex_destroy(&lock);
            printf("Valor final do contador: %d\n", contador);
            break;
        }

        case 4: {
            pthread_t t1, t2;
            sem_init(&empty, 0, TAM);
            sem_init(&full, 0, 0);
            pthread_mutex_init(&mutex, NULL);
            pthread_create(&t1, NULL, produtor, NULL);
            pthread_create(&t2, NULL, consumidor, NULL);
            pthread_join(t1, NULL);
            pthread_join(t2, NULL);
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            break;
        }

        case 5: {
            pthread_t filosofos[NUM_FILOSOFOS];
            int ids[NUM_FILOSOFOS];

            for(int i = 0; i < NUM_FILOSOFOS; i++)
                sem_init(&garfo[i], 0, 1);

            for(int i = 0; i < NUM_FILOSOFOS; i++) {
                ids[i] = i;
                pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
            }

            for(int i = 0; i < NUM_FILOSOFOS; i++)
                pthread_join(filosofos[i], NULL);

            for(int i = 0; i < NUM_FILOSOFOS; i++)
                sem_destroy(&garfo[i]);

            break;
        }

        case 0: {
            printf("Encerrando...\n");
            break;
        }

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
