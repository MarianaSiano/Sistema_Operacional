#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <pthread.h>
#include <semaphore.h>
//#include <sys/wait.h>

//Somaforos
#define BUFFER_SIZE 5
sem_t empty, full;
pthread_mutex_t mutex;
int buffer[BUFFER_SIZE];
int index_prod = 0, index_cons = 0;

//Criação de 5 Threads
void *thread_func(void *arg)
{
    printf("Thread ID => %lu\n", pthread_self());
    return NULL;
}

//Exclusao Mútua
int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg)
{
    for(int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

//Semaforo
void *producer(void *arg)
{
    for(int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[index_prod] = i;
        index_prod = (index_prod + 1) % BUFFER_SIZE;
        printf("Produzido => %d\n", i);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for(int i = 1; i <= 10; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[index_cons];
        index_cons = (index_cons + 1) % BUFFER_SIZE;
        printf("Consumidor => %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    int opcao;

    do {
        printf("\n================= MENU =================\n");
        printf("1.Criacao de 3(Três) Processos Filhos");
        printf("2. Criacao de 5 (Cinco) Threads");
        printf("3. Exclusao Mutua");
        printf("4. Semaforo");
        printf("0. Sair\n");
        printf("Escolha uma opcao => ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                for(int i = 0; i < 3; i++) {
                    pid_t pid = fork();
                    if(pid == 0) {
                        printf("Processo filho (PID: %d), PID do pai => %d\n", getpid(), getppid());
                        return 0; //Termina o processo filho
                    }
                }

                //Processo pai espera todos os filhos terminarem
                for(int i = 0; i < 3; i++)
                    wait(NULL);

                printf("Processo pai finalizado\n");
                break;
            }

            case 2: {
                pthread_t threads[5];

                for(int i = 0; i < 5; i++)
                    pthread_create(&threads[i], NULL, thread_func, NULL);

                for(int i = 0; i < 5; i++)
                    pthread_join(threads[i], NULL);

                break;
            }

            case 3: {
                pthread_t threads[10];

                for(int i = 0; i < 10; i++)
                    pthread_create(&threads[i], NULL, increment, NULL);

                for(int i = 0; i < 10; i++)
                    pthread_join(threads[i], NULL);

                printf("Counter => %d\n", counter);
                break;
            }

            case 4: {
                sem_init(&empty, 0, BUFFER_SIZE);
                sem_init(&full, 0, 0);
                pthread_mutex_init(&mutex, NULL);

                pthread_t prod_thread, cons_thread;
                pthread_create(&prod_thread, NULL, producer, NULL);
                pthread_create(&cons_thread, NULL, consumer, NULL);

                pthread_join(prod_thread, NULL);
                pthread_join(cons_thread, NULL);

                sem_destroy(&empty);
                sem_destroy(&full);
                pthreead_mutex_destroys(&mutex);
                break;
            }

            case 0: {
                printf("Encerrando o programa...\n");
                break;
            }

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    return 0;
}