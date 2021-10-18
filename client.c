#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

#define SH_SIZE 256

/*void *readFIFO(void *param)
{

}*/
void CmUnsub(char *NameEvent);
void CmSub(char *NameEvent);
int WaitConf();
void CmList();
void CleanFile();
void CmAsk();
void *hilolecturaShm(void *param);

char Events[4][10] = {"null", "null", "null", "null"};

int main(int argc, char *argv[])
{
    pthread_t threadID;
    pthread_create(&threadID, NULL, &hilolecturaShm, NULL);

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
            printf("%s\n", cmd);
        }
    }

    exit(EXIT_SUCCESS);
}
void CmSub(char *NameEvent)
{
    //Proceso de cuando se pide sub
    int shm_fd = shm_open("/shm0", O_RDWR, 0600);
    if (shm_fd < 0)
    {
        perror("shm memory error: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is opened with fd: %d\n", shm_fd);

    void *map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (map == MAP_FAILED)
    {
        perror("Mapping failed: ");
        exit(EXIT_FAILURE);
    }
    char *cmd = (char *)map;
    for (int i = 0; i < 32; i++) //Para limpiar shm
    {
        cmd[i] = '\0';
    }
    for (int i = 0; i < 32; i++)
    {
        cmd[0] = 's';
        cmd[1] = 'u';
        cmd[2] = 'b';
        cmd[3] = ' ';
        cmd[i + 4] = NameEvent[i];
    }

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
    int shm_fd = shm_open("/shm0", O_RDWR, 0600);
    if (shm_fd < 0)
    {
        perror("shm memory error: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd);

    void *map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (map == MAP_FAILED)
    {
        perror("Mapping failed: ");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 50; i++)
    {
        char *readsm = (char *)map;
        printf("Verif: %s\n", readsm);
        if (strcmp(readsm, "CONFIRMADO\n") == 0)
        {
            return 1;
            break;
        }
    }
    return 0;
}
void CleanFile()
{
    //Porceso de cuando se pide clean file
    int shm_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if (shm_fd < 0)
    {
        perror("shm memory error: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is opened with fd: %d\n", shm_fd);

    void *map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (map == MAP_FAILED)
    {
        perror("Mapping failed: ");
        exit(EXIT_FAILURE);
    }
    char *cmd = (char *)map;
    for (int i = 0; i < 32; i++) //Para limpiar shm
    {
        cmd[i] = '\0';
    }
}
void CmAsk()
{
    int shm_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if (shm_fd < 0)
    {
        perror("shm memory error: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is opened with fd: %d\n", shm_fd);

    void *map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (map == MAP_FAILED)
    {
        perror("Mapping failed: ");
        exit(EXIT_FAILURE);
    }
    char *cmd = (char *)map;
    for (int i = 0; i < 32; i++) //Para limpiar shm
    {
        cmd[0] = 'a';
        cmd[1] = 's';
        cmd[2] = 'k';
        cmd[3] = ' ';
    }
}
void *hilolecturaShm(void *param)
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
    while (1)
    {
        char *readsm = (char *)map;

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
}
