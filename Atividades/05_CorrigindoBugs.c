#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <process.h>
#include <pthread.h>
#include <semaphore.h>
//#include <sys/wait.h>

//Atividade 5 - Correção de Bugs

int main()
{
    //Atividade 5.1 - Por que este código cria Processos Zumbis?
    int opcao;
    do {
        printf("\n======================= MENU  =======================\n");
        printf("\n======================= ATIVIDADE 5.1 =======================\n");
        printf("1. Codigo Original\n");
        printf("2. Codigo Corrigido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao => ");

        switch(opcao) {
            case 1: {
                //Codigo original
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