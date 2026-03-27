#include <stdio.h>
#include "parking.h" //para incluir la biblioteca en el directorio actual en el que estamos trabajando
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#define CANT_SEMAFOROS 79
#define TAM 1024

struct mensaje {
    long tipo;
    char texto[100];
};


void mensaje_sigint();
int funciOn_llegada(HCoche hc); 
void semSIGNAL (int num_sem, int semID);
void funcAparcamiento (int longitudCoche, int a );
// Fucntioned

void modoEjecucion (char *arg3, char *arg4);

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

    if (strcmp(argv[3], "PA") != 0 && strcmp(argv[3], "PD") != 0){
        perror("El argumento permitido solo puede ser PA o PD.");
        exit(EXIT_FAILURE);
    } else if (strcmp(argv[3], "PA") == 0 && strcmp(argv[4], "PD") == 0){
        perror("Introduce una combinacion de argumentos valida.");
        exit(EXIT_FAILURE);
    }

    //creacion de la señal que vamos a modificar.

    /*struct sigaction ss;
    ss.sa_handler = mensaje_sigint();
    sigaction(SIGINT, )*/



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
        perror("Error en la creacion de la zona de memoria compartida.");
        exit(EXIT_FAILURE);
    }

    /*PARKING_INICIO(velocidad, choferes, semid, msgid, shmid);
    if (PARKING_INICIO(velocidad, choferes, semid, msgid, shmid) < 0){
        perror("Error en la ejecucion de PARKING_InICIO");
        exit(EXIT_FAILURE);
    }
    */
    /*PARKING_aparcar();
    PARKING_desaparcar();*/

    //int hola = funciOn_llegada();
    printf("Código ejecutado exitosamente !!!\n");
    fflush(stdout);
    return 0;


}

void mensaje_Sigint(int i){
    //codigo :)
}

void modoEjecucion (char *arg3, char *arg4){

    if (strcmp(arg3, "PA") == 0){
        printf("Daremos prioridad a los coches que se van a aparcar. \n");
    }

    if (strcmp(arg3, "PD") == 0){
        printf("Daremos prioridad a los coches que se van a desaparcar. \n");
    }
    /*witch(arg3){
        case 'PA':
            printf("Daremos prioridad a los coches que se van a aparcar. \n");
            break;
        case 'PD':
            printf("Daremos prioridad a los coches que se van a desaparcaar \n");
            fflush(stdout);
            break;
    }*/
}