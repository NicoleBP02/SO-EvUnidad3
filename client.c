#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define SH_SIZE 256

void CmUnsub(char *NameEvent);
void CmSub(char *NameEvent);
int WaitConf();
void CmList();
void CleanFile();
void CmAsk();
void *threadReadMsg(void *param);

char Events[4][10] = {"null", "null", "null", "null"};

int main(int argc, char *argv[])
{
    pthread_t threadID;
    pthread_create(&threadID, NULL, &threadReadMsg, NULL);

    char input[32] = "nada";
    while (1)
    {
        fgets(input, 32, stdin);
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
        // Tokenizar lo que se escribe por la terminal para ver a que comando corresponde (que seria la posicion 0)
        int sub = strcmp(action, "sub");
        int unsub = strcmp(action, "unsub");
        int list = strcmp(action, "list\n");
        int ask = strcmp(action, "ask\n");
        if (sub == 0)
        {
            CmSub(nameEv);
        }
        else if (unsub == 0)
        {
            CmUnsub(nameEv);
        }
        else if (list == 0)
        {
            CmList();
        }
        else if (ask == 0)
        {
            printf("Ask\n");
            CmAsk();
            sleep(2);
        }
    }

    exit(EXIT_SUCCESS);
}
void CmSub(char *NameEvent)
{
    //Proceso de cuando se pide sub
    int exists = WaitConf();

    if (exists == 1)
    {
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
    CleanFile();
}
void CmUnsub(char *NameEvent)
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
void CmList()
{
    //Proceso de cuando se pide list
    for (int i = 0; i < 4; i++)
    {
        printf("Evento %d: %s\n", i, Events[i]);
    }
}

int WaitConf()
{
    
    return 0;
}

void CmAsk()
{
    
}
/*void *threadReadMsg(void *param)
{
    while (1)
    {
        char *token = strtok(readsm, " ");

        char *action = "NULL";

        char *nameEv = "NULL";


        for (int i = 0; token != NULL; i++)
        {
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

        int trg = strcmp(action, "tgr");

        if (trg == 0)
        {
            printf("tgr\n");
            printf("El evento %s fue publicado\n", nameEv);
        }
    }
}*/
