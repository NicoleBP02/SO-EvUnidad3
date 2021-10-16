#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>

void CmExit(char *buffer);
void CmAdd(char *buffer);
void CmRemove(char *buffer);
void CmTrigger(char *buffer);
void CmList(char *buffer);

void *hilolecturafifo(void *param);

// Declaracion de variable que funcionara como switch de manera global
int conv = 6;

int main(int argc, char **argv)
{
    pthread_t threadID;
    pthread_create(&threadID, NULL, &hilolecturafifo, NULL);

    char respuesta[16];
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
    return NULL;
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
void *hilolecturafifo(void *param) //Proceso hilo
{
    //Todo el proceso para leer el fifo
}