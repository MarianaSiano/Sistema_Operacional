#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <process.h>
//#include <sys/wait.h>

//1.1 - Processo de 3 Processos Filhos
int main()
{
    for(int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if(pid == 0) { //Processo filho
            printf("Processo filho (PID: %d), PID do pai: %d\n", getpid(), getppid());
            return 0; //Termina o processo filho
        }
    }

    //Processo pai espera todos os filhos terminarem
    for(int i = 0; i < 3; i++)
        wait(NULL);

    printf("Processo pai finalizado!\n");
    return 0;
}