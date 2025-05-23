#include <stdio.h>
#include <stdlib.h>

int main()
{
    int opcao;

    do {
        printf("\n================= MENU =================\n");
        printf("1.");
        printf("0. Sair\n");
        printf("Escolha uma opcao => ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
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