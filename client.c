#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Librerias para FIFO
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void *readFIFO(void *param)
{
    int fd;

    // FIFO file path
    char *myfifo = "~/reps/SO-EvaluacionUnidad3/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    // mkfifo(myfifo, 0666);
    while (1)
        // Open FIFO for write only
        fd = open("myfifo", O_WRONLY);
    if (fd == 1)
    {
        return 1;
    }
    // Commands logic
    return NULL;
}

int main(int argc, char *argv[])
{
    // Se crea el hilo para leer el FIFO
    pthread_t threadID;
    pthread_create(&threadID, NULL, &readFIFO, NULL);

    /*
        Se maneja la lectura de terminal
        La lectura de terminal se realizara con un ciclo infinito 
        que compara los valores tokenizados del string con los comandos 
        aceptados, modificando un entero de comparacion para luego 
        segun este mismo modificar un entero de switch 
    */
    int conv = 6;
    char respuesta[16];
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
    }

    exit(EXIT_SUCCESS);
}