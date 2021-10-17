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

void CmExit();
void CmAdd(char *NameEvent);
void CmRemove(char *NameEvent);
void CmTrigger(char *NameEvent);
void CmList();

void *hilolecturaTerm(void *param);

// Declaracion de variable que funcionara como switch de manera global
int conv = 6;
char Events[4][10] = {"null", "null", "null", "null"};
char a[10] = "asd";

int main(int argc, char **argv)
{
    pthread_t threadID;
    pthread_create(&threadID, NULL, &hilolecturaTerm, NULL);

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
    char *cmd = (char *)map;
    cmd[0] = 'A';
    cmd[1] = 'B';
    cmd[2] = 'C';
    cmd[3] = '\n';
    cmd[4] = '\0';

    sleep(20);
}
void CmExit()
{
    //Proceso de cuando se pide exit
    printf("Exit\n");
    exit(0);
}
void CmAdd(char *NameEvent)
{
    //Proceso de cuando se pide add
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(Events[i], "null") == 0)
        {
            strcpy(Events[i], NameEvent);
            printf("Evento %d: %s", i, Events[i]);
            break;
        }
    }
}
void CmRemove(char *NameEvent)
{
    //Proceso de cuando se pide remove
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(Events[i], NameEvent) == 0)
        {
            strcpy(Events[i], "null");
            printf("Evento %d: %s\n", i, Events[i]);
            break;
        }
    }
}
void CmTrigger(char *buffer)
{
    //Porceso de cuando se pide trigger
}
void CmList()
{
    //Proceso de cuando se pide list
    for (int i = 0; i < 4; i++)
    {
        printf("Evento %d: %s\n", i, Events[i]);
    }
}
void *hilolecturaTerm(void *param) //Proceso hilo
{
    char input[16] = "nada";
    while (1)
    {
        fgets(input,16, stdin);
        // printf("------------------------Respuesta %s ----------------------------------\n", respuesta);
        for (int i = 0; input[i] != '\0'; ++i)
        {
            input[i] = tolower(input[i]);
        }
        // Tokenizar lo que se escribe por la terminal para ver a què comando corresponde (que seria la posicion 0)
        char *token = strtok(input, " ");

        char *action = NULL;

        char *nameEv;

        // loop through the string to extract all other tokens

        for (int i = 0; token != NULL; i++)
        {
            // printf("Entro al ciclo");
            if (i == 0)
            {
                action = token;
            }
            else if (i == 1)
            {
                nameEv = token;
            }
            token = strtok(NULL, " ");
        }
        
        int exitEv = strcmp(action, "exit");
        int addEv = strcmp(action, "add");
        int removeEv = strcmp(action, "remove");
        int triggerEv = strcmp(action, "trigger");
        int listCl = strcmp(action, "list\n");

        // Cambia el valor de conv segun la entrada de usuario
        if (exitEv == 0)
        {
            CmExit();
            conv = 1;
        }
        else if (addEv == 0)
        {
            printf("Add\n");
            CmAdd(nameEv);
            conv = 2;
        }
        else if (removeEv == 0)
        {
            printf("Remove\n");
            CmRemove(nameEv);
            conv = 3;
        }
        else if (triggerEv == 0)
        {
            printf("Trigger\n");
            conv = 4;
        }
        else if (listCl == 0)
        {
            printf("List\n");
            CmList();
            conv = 5;
        }
    }
    return NULL;
}