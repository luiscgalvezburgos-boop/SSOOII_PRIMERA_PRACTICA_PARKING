#include <stdio.h>
#include "parking.h" //para incluir la biblioteca en el directorio actual en el que estamos trabajando
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>

#define CANT_SEMAFOROS 79
#define TAM 1024

struct mensaje {
    long tipo;
    char texto[100];
};

void mensaje_sigint(int i );
void semSIGNAL (int num_sem, int semID);
void funcAparcamiento (int longitudCoche, int a );

// Fucntioned
int funciOn_llegada(HCoche hc); 

int main (int argc, char *argv[]){
    
    if (argv[1] == NULL || argv[2] == NULL){
        printf("Debes ingresar como minimo mas de dos argumentos!!!\n");
        exit(EXIT_FAILURE);
    } else if (argc > 5){
        printf("Debes ingresar como maximo 4 argumentos!!!\n");
        exit(EXIT_FAILURE);
    }

    int velocidad = atoi(argv[1]);
    int choferes = atoi(argv[2]);

    printf(" Velocidad: %d \n Choferes: %d", velocidad, choferes);
    fflush(stdout); //comentario random
    
    if (velocidad < 0 ){
        perror("Debes introducir un valor mayor o igual a 0 como primer parametro!!");
        exit(EXIT_FAILURE);
    } else if (choferes <= 0){
        perror("Debes introducir una cantidad de choferes mayor que 0 en el segundo parametro!!");
        exit(EXIT_FAILURE);
    }

    /*struct sigaction ss;
    ss.sa_handler = mensaje_sigint;*/


    // CREACION SEMAFORO
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

    // CREACION BUZONES
    int msgid;
    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
    struct mensaje msg;

    if (msgid < 0){
        perror("Error en la creacion del buzon.");
        exit(EXIT_FAILURE);
    }

    // MEMORIA COMPARTIDA
    char *punteroAMemoriaCompartida = NULL;
    int shmid = shmget(IPC_PRIVATE, TAM, IPC_CREAT | 0600);

    if (shmid < 0){
        perror("Error en el fork().");
        exit(EXIT_FAILURE);
    }

    PARKING_INICIO(velocidad, choferes, semid, msgid, shmid);
    /*PARKING_aparcar();
    PARKING_desaparcar();*/
    printf("Código ejecutado exitosamente !!!\n");
    fflush(stdout);
    return 0;
}

void mensaje_Sigint(int i){
    //codigo :)
}