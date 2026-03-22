#include <stdio.h>
#include "parking.h" //para incluir la biblioteca en el directorio actual en el que estamos trabajando
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>

#define CANT_SEMAFOROS 10
#define TAM 1024

void semSIGNAL (int num_sem, int semID);

int main (int argc, char *argv[]){
    int semid = semget(IPC_PRIVATE, CANT_SEMAFOROS, IPC_CREAT | 0600);

    if (semid < 0)
    {
        perror("Error en la creacion del semaforo.");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid, 0, SETVAL, 0) < 0){ //Semaforo del padre
		perror("Error al inicializar el semáforo.");
		exit(EXIT_FAILURE);
	}

    char *punteroAMemoriaCompartida = NULL;
    int shmid = shmget(IPC_PRIVATE, TAM, IPC_CREAT | 0600);

    if (shmid < 0){
        perror("Error en el fork().");
        exit(EXIT_FAILURE);
    }

    printf("Código ejecutado exitosamente !!!\n");
    fflush(stdout);
    return 0;
}