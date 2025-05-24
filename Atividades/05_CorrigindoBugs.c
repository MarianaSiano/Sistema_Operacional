#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <process.h>
#include <pthread.h>
#include <semaphore.h>
//#include <sys/wait.h>

//Atividade 5.2
int counter = 0;
pthread_mutex_t lock;

void *increment(void *arg)
{
    for(int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

//Atividade 5.3 - Corrigir Deadlock (Inversão nos Semáforos)
sem_t empty, full;
int buffer[5], index = 0;

void produtor()
{
    for(int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        buffer[index++] = i;
        sem_post(&full);
    }
}

//Atividade 5 - Correção de Bugs
int main()
{
    int opcao;
    do {
        printf("\n======================= MENU  =======================\n");
        printf("\n======================= ATIVIDADE 5.1 =======================\n");
        printf("1. Codigo Corrigido de Criacao de Processos Zumbiso\n");
        printf("\n======================= ATIVIDADE 5.2 =======================\n");
        printf("2. Corrigir Erros de Sincronizacao");
        printf("\n======================= ATIVIDADE 5.3 =======================\n");
        prinf("3. Codigo Corrigido de Ocorrencia de Deadlock\n");
        prinf("\n======================= ATIVIDADE 5.4 =======================\n");
        prinf("4.\n");
        prinf("\n======================= ATIVIDADE 5.5 =======================\n");
        prinf("\n\n");
        prinf("\n\n");
        prinf("\n======================= ATIVIDADE 5.6 =======================\n");
        prinf("\n\n");
        prinf("\n\n");
        prinf("\n======================= ATIVIDADE 5.7 =======================\n");
        prinf("\n\n");
        prinf("\n\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao => ");

        switch(opcao) {
            case 1: {
                //Codigo corrigido com wait()
                for(int i = 0; i < 3; i++) {
                    pid_t pid = fork();

                    if(pid == 0) {
                        printf("Filho %d criado\n", getpid());
                        return 0;
                    }
                }

                //Espere todos os filhos
                for(int i = 0; i < 3; i++)
                    wait(NULL);

                printf("Pai Finalizado\n");
                break;
            }

            case 2: {
                pthread_t t1, t2;

                pthread_mutex_initi(&lock, NULL);

                pthread_create(&t1, NULL, increment, NULL);
                pthread_create(&t2, NULL, increment, NULL);

                pthread_join(t1, NULL);
                pthread_join(t2, NULL);

                printf("Counter => %d\n", counter);

                pthread_mutex_destroy(&lock);
                break;
            }

            case 3: {
                break;
            }

            case 0: {
                printf("Encerrando o programa.\n");
                break;
            }

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}