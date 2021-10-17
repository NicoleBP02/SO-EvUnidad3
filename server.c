#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

#define SH_SIZE 16

void CmExit(char *buffer);
void CmAdd(char *buffer);
void CmRemove(char *buffer);
void CmTrigger(char *buffer);
void CmList(char *buffer);

//void *hilolecturamsg(void *param);

// Declaracion de variable que funcionara como switch de manera global
int conv = 6;

int main(int argc, char **argv)
{
    /*pthread_t threadID;
    pthread_create(&threadID, NULL, &hilolecturamsg, NULL);*/

    int shm_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if (shm_fd < 0)
    {
        perror("shm memory error: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd);

    if (ftruncate(shm_fd, SH_SIZE * sizeof(char)) < 0)
    {
        perror("Truncation failed: ");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "The memory region is truncated.\n");

    void *map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (map == MAP_FAILED)
    {
        perror("Mapping failed: ");
        exit(EXIT_FAILURE);
    }
    char* ptr = (char*)map;
     ptr[0] = 'A';
     ptr[1] = 'B';
     ptr[2] = 'C';
     ptr[3] = '\n';
     ptr[4] = '\0';

    /*char respuesta[16];
    while (1)
    {
        scanf("%s", respuesta);
        // printf("------------------------Respuesta %s ----------------------------------\n", respuesta);
        for (int i = 0; respuesta[i] != '\0'; ++i)
        {
            respuesta[i] = tolower(respuesta[i]);
        }
        // Tokenizar lo que se escribe por la terminal para ver a què comando corresponde (que seria la posicion 0)
        int exitEv = strcmp(respuesta, "exit");
        int addEv = strcmp(respuesta, "add");
        int removeEv = strcmp(respuesta, "remove");
        int triggerEv = strcmp(respuesta, "trigger");
        int listCl = strcmp(respuesta, "list");

        // Cambia el valor de conv segun la entrada de usuario
        if (exitEv == 0)
        {
            conv = 1;
        }
        else if (addEv == 0)
        {
            conv = 2;
        }
        else if (removeEv == 0)
        {
            conv = 3;
        }
        else if (triggerEv == 0)
        {
            conv = 4;
        }
        else if (listCl == 0)
        {
            conv = 5;
        }
    }
    return NULL;*/
}
void CmExit(char *buffer)
{
    //Proceso de cuando se pide exit
}
void CmAdd(char *buffer)
{
    //Proceso de cuando se pide add
}
void CmRemove(char *buffer)
{
    //Proceso de cuando se pide remove
}
void CmTrigger(char *buffer)
{
    //Porceso de cuando se pide trigger
}
void CmList(char *buffer)
{
    //Proceso de cuando se pide list
}
/*void *hilolecturamsg(void *param) //Proceso hilo
{
    //Todo el proceso para leer el fifo
}*/