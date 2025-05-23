#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <windows.h>
// #include <process.h>
#include <sys/wait.h>

int main()
{
    for(int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if(pid < 0) {
            perror("Erro ao criar processo filho");
            exit(1);
        }

        else if(pid == 0) {
            //Codigo do processo filho
            printf("Processo filho (PID: %d), PID do pai: %d\n", getpid(), getppid());
            exit(0); //Filho finaliza aqui
        }
    }

    //Codigo do processo pai
    for(int i = 0; i < 3; i++)
        wait(NULL); //Espera os 3 filhos finalizarem

    printf("Processo pai finalizado\n");
    return 0;
}