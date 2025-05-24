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

//Atividade 5.6 - Correção Condição de Corrida com Cadeiras
#define NUM_CLIENTES 10
#define NUM_CADEIRAS 5

sem_t clientes, barbeiro, mutex;
int cadeiras_livres = NUM_CADEIRAS;

#define NUM_FILOSOFOS 5
sem_t garfo[NUM_FILOSOFOS];

void *cliente(void *arg)
{
    int id = *(int*) arg;
    sleep(rand() % 3); //Chegada aleatoria

    sem_wait(&mutex);

    if(cadeiras_livres > 0) {
        cadeiras_livres--;
        printf("Cliente %d sentou. Cadeiras livres => %d\n", id, cadeiras_livres);
        sem_post(&clientes); //Avisa o barbeiro
        sem_post(&mutex);

        sem_wait(&barbeiro); //Espera ser atentido
        printf("Cliente %d esta cortando o cabelo. \n", id);
    }

    else {
        sem_post(&mutex);
        print("Cliente %d foi embora. Sem cadeirdas disponiveis\n", id);
    }

    free(arg);
    return NULL;
}

void *barbeiro_func(void *arg)
{
    while(1) {
        sem_wait(&clientes); //Espera por cliente
        sem_wait(&mutex);
        cadeiras_livres++; //Cliente saiu da espera
        sem_post(&barbeiro); //Chama o cliente
        sem_post(&mutex);

        printf("Barbeiro esta cortando cabelo... \n");
        sleep(2); //Simula tempo de corte
        printf("Barbeiro terminou o corte\n");
    }

    return NULL;
}

void *filosofo(void *arg)
{
    int id = *(int*) arg;

    while(1) {
        //Pensando
        printf("Filoso %d esta pensando../n", id);
        sleep(rand() % 3 + 1);

        //Tenta pegae os garfos (com ordem alterada para evitar deadlock)
        if(id % 2 == 0) {
            sem_wait(&garfo[(id + 1) % NUM_FILOSOFOS]); //Pega gargo da difença
            sem_wait(&garfo[id]); //Pega garfo da esquerda
        }

        else {
            sem_wait(&garfo[id]); //Pega o garfo da direita
            sem_wait(&garfo[(id + 1) % NUM_FILOSOFOS]); //Pega o garfo da esquerda
        }

        //Comendo
        printf("Filosofo %d esta comendo...\n", id);
        sleep(rand() % 2 + 1);

        //Solta os garfos
        sem_post(&garfo[id]);
        sem_post(&garfo[(id + 1) % NUM_FILOSOFOS]);

        printf("Filosofo %d terminou de comer e largou os garfos.\n", id);
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
        printf("1. Criacao de Processos Zumbiso\n");
        printf("\n======================= ATIVIDADE 5.2 =======================\n");
        printf("2. Corrigir Erros de Sincronizacao");
        printf("\n======================= ATIVIDADE 5.3 =======================\n");
        prinf("3. Ocorrencia de Deadlock - Cliente\n");
        prinf("4. Ocorrencia de Deadlock - Filosofo\n");
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
                pthread_t t_barber;
                pthread_t t_clientes[NUM_CLIENTES];

                sem_init(&clientes, 0, 0);
                sem_init(&barbeiro, 0, 0);
                sem_init(&mutex, 0, 1);

                pthread_create(&t_barber, NULL, barbeiro_func, NULL);

                for(int i = 0; i < NUM_CLIENTES; i++) {
                    int *id = malloc(sizeof(int));
                    *id = i + 1;
                    pthread_create(&t_clientes[i], NULL, cliente, id);
                    sleep(1); //Espaça a chegada dos clientes
                }

                for(int i = 0; i < NUM_CLIENTES; i++)
                    pthread_join(t_clientes[i], NULL);

                //Aviso: o barbeiro roda indefinidamente

                sem_destroy(&clientes);
                sem_destroy(&barbeiro);
                sem_destroy(&mutex);
                break;
            }

            case 4: {
                pthread_t filosofos[NUM_FILOSOFOS];
                int ids[NUM_FILOSOFOS];

                for(int i = 0; i < NUM_FILOSOFOS; i++)
                    sem_init(&garfo[i], 0, 1);

                for(int i = 0; i < NUM_FILOSOFOS; i++) {
                    ids[i] = i;
                    pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
                }

                for(int i = 0; i < NUM_FILOSOFOS; i++) 
                    pthread_join(filosofos[i], NULL); //Este join nunca termina, pois os filosofos sao infinitos
                
                for(int i = 0; i < NUM_FILOSOFOS; i++)
                    sem_destroy(&garfo[i]);
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