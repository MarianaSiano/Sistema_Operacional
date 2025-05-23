#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <pthread.h>
//#include <sys/wait.h>

void *thread_func(void *arg)
{
    printf("Thread ID => %lu\n", pthread_self());
    return NULL;
}

int main()
{
    int opcao;

    do {
        printf("\n================= MENU =================\n");
        printf("1.Criacao de 3(Três) Processos Filhos");
        printf("2. Criacao de 5 (Cinco) Threads");
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
                    pthread_joid(threads[i], NULL);

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