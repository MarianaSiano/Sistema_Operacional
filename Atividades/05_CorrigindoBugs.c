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

//Original
void *increment1(void *arg)
{
    for(int i = 0; i < 1000; i++)
        counter++;
    return NULL;
}

//Corrigido
void *increment(void *arg)
{
    for(int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

//Atividade 5 - Correção de Bugs
int main()
{
    int opcao;
    do {
        printf("\n======================= MENU  =======================\n");
        printf("\n======================= ATIVIDADE 5.1 =======================\n");
        printf("1. Codigo Original\n");
        printf("2. Codigo Corrigido\n");
        printf("\n======================= ATIVIDADE 5.2 =======================\n");
        printf("3. Codigo Original\n");
        printf("4. Corrigir Erros de Sincronizacao");
        printf("0. Sair\n");
        printf("Escolha uma opcao => ");

        switch(opcao) {
            case 1: {
                //Codigo original da atividade 5.1 - Por que este código cria Processos Zumbis
                for(int i = 0; i < 3; i++) {
                    if(fork() == 0) {
                        print("Filho %d criado\n", getpid());
                        return 0;
                    }
                }
                sleep(5);
                printf("Pai Finalizado\n");
                break;
            }

            case 2: {
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

            case 3: {
                pthread_t t1, t2;
                pthread_create(&t1, NULL, increment1, NULL);
                pthread_create(&t2, NULL, increment1, NULL);
                printf("Couter => %d\n", counter);
                break;
            }

            case 4: {
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