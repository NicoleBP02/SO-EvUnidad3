# Evaluacion 3 de sistemas operativos

## Compilación

La compilación de los programas server.c y client.c se hace con los siguientes comandos de consola respectivamente
--> gcc -Wall server.c -o server -lrt -lpthread 
--> gcc -Wall client.c -o client -lrt -lpthread 

## Despliege

El servidor se ejecuta a partir del programa y los clientes tambien, ejecutando el archivo compilado desde la terminal.

./server
./client