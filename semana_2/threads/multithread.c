#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//variavel global pra ser alterada nas threads
int global = 0;
void* ThreadFunction(void* varg)
{
    int myid = getpid();

    static int count = 0;
    count++;
    global++;
    printf("Thread ID: %d, Static: %d, Global: %d\n", myid, count, global);
}

int main()
{
    int i;//declaracao pro loop
    pthread_t thread_id;

    for(i = 0; i < 3; i++)
    {
        pthread_create(&thread_id, NULL, ThreadFunction, NULL);
    }
    pthread_exit(NULL);
    return 0;
}

//Aqui temos um exemplo de threads, onde a variavel global eh compartilhada entre as threads.
/*
Pergunta: Se a variavel global eh compartilhada entre as threads, o que acontece se uma thread que nao era para alterar a variavel alterar o valor da variavel global?

Aqui nao acontece, mas chega bem pertinho de um exemplo de impasse, assunto futuro
*/