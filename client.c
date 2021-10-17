#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define SH_SIZE 16

/*void *readFIFO(void *param)
{

}*/

int main(int argc, char *argv[])
{
    int shm_fd = shm_open("/shm0", O_RDONLY, 0600);
    if (shm_fd < 0)
    {
        perror("shm memory error: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd);

    void *map = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    if (map == MAP_FAILED)
    {
        perror("Mapping failed: ");
        exit(EXIT_FAILURE);
    }

    char *cmd = (char *)map;
    fprintf(stdout, "The contents of shared memory object: %s\n", cmd);

    if (munmap(cmd, SH_SIZE) < 0)
    {
        perror("Unmapping failed: ");
        exit(EXIT_FAILURE);
    }
    // Se crea el hilo para leer el FIFO
    /*pthread_t threadID;
    pthread_create(&threadID, NULL, &readFIFO, NULL);
    */

    /*
        Se maneja la lectura de terminal
        La lectura de terminal se realizara con un ciclo infinito 
        que compara los valores tokenizados del string con los comandos 
        aceptados, modificando un entero de comparacion para luego 
        segun este mismo modificar un entero de switch 
    */
    //int conv = 6;
    /*char respuesta[16];
    while (1)
    {
        scanf("%s", respuesta);
        // printf("------------------------Respuesta %s ----------------------------------\n", respuesta);
        for (int i = 0; respuesta[i] != '\0'; ++i)
        {
            respuesta[i] = tolower(respuesta[i]);
        }
        // Tokenizar lo que se escribe por la terminal para ver a que comando corresponde (que seria la posicion 0)
        int sub = strcmp(respuesta, "sub");
        int unsub = strcmp(respuesta, "unsub");
        int list = strcmp(respuesta, "list");
        int ask = strcmp(respuesta, "ask");
        // Cambia el valor de conv segun la entrada de usuario
        if (sub == 0)
        {
            conv = 1;
        }
        else if (unsub == 0)
        {
            conv = 2;
        }
        else if (list == 0)
        {
            conv = 3;
        }
        else if (ask == 0)
        {
            conv = 4;
        }
    }*/

    exit(EXIT_SUCCESS);
}