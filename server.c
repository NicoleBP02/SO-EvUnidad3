#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SH_SIZE 256

typedef struct message
{
    char command[10];
    int id_queue;
    char msg[64];
}message;

typedef struct event
{
    char event[64];
    char subClients[10][64];
}event;

void CmExit();
void CmAdd(char *NameEvent);
void CmRemove(char *NameEvent);
void CmTrigger(char *NameEvent);
void CmList();
int EventExists(char *NameEvent);
void *threadReadTerm(void *param);


int main(int argc, char **argv)
{
    key_t queue_key = ftok("./queue_key.txt", 1);
    int mqi;
    mqi = msgget(queue_key, IPC_CREAT | 0660);

    pthread_t threadID;
    pthread_create(&threadID, NULL, &threadReadTerm, NULL);

/*
    while (1)
    {
        // Tokenizar lo que se escribe por la terminal para ver a què comando corresponde (que seria la posicion 0)
        char *token = strtok(readsm, " ");

        char *action = "NULL";

        char *nameEv = "NULL";

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

        int ask = strcmp(action, "ask");
        int sub = strcmp(action, "sub");
        int unsub = strcmp(action, "unsub");

        if (sub == 0)
        {
            printf("Sub\n");
            if (EventExists(nameEv) == 1){
                WriteFile("CONFIRMADO\n");
            };
        }
        else if (unsub == 0)
        {
            printf("Unsub\n");
        }

        if (ask == 0)
        {
            printf("Ask\n");
            char allEvents[80]= "";
            strcat(allEvents, Events[0]);
            strcat(allEvents, " ");
            strcat(allEvents, Events[1]);
            strcat(allEvents, " ");
            strcat(allEvents, Events[2]);
            strcat(allEvents, " ");
            strcat(allEvents, Events[3]);
            WriteFile(allEvents);
        }


        //printf("Verif: %s\n", readsm);
        //sleep(5);
    }

    //sleep(20);
}
void CmExit()
{
    //Proceso de cuando se pide exit
    printf("Exit\n");
    CmTrigger("exit");
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
void CmTrigger(char *NameEvent)
{
    
}
void CmList()
{
    //Proceso de cuando se pide list
    for (int i = 0; i < 4; i++)
    {
        printf("Evento %d: %s\n", i, Events[i]);
    }
}
int EventExists(char *NameEvent)
{
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(Events[i], NameEvent) == 0)
        {
            return 1;
            break;
        }
    }
    return 0;
    
}
void *threadReadTerm(void *param) //Proceso hilo
{
    char input[32] = "nada";
    while (1)
    {
        fgets(input,32, stdin);
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
        
        int exitEv = strcmp(action, "exit\n");
        int addEv = strcmp(action, "add");
        int removeEv = strcmp(action, "remove");
        int triggerEv = strcmp(action, "trigger");
        int listCl = strcmp(action, "list\n");

        // Cambia el valor de conv segun la entrada de usuario
        if (exitEv == 0)
        {
            CmExit();
        }
        else if (addEv == 0)
        {
            printf("Add\n");
            CmAdd(nameEv);
        }
        else if (removeEv == 0)
        {
            printf("Remove\n");
            CmRemove(nameEv);
        }
        else if (triggerEv == 0)
        {
            printf("Trigger\n");
            CmTrigger(nameEv);
        }
        else if (listCl == 0)
        {
            printf("List\n");
            CmList();
        }
    }
    return NULL;
}*/
