#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 


void* ThreadFunction(void* varg)
{
    sleep(1);
    printf("Function called by thread \n");
    return NULL;
}

int main()
{
    pthread_t thread_id; // thread identifier
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, ThreadFunction, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}

/*
Thread eh bem parecido com processos, mas a diferenca eh que threads compartilham o mesmo espaco de memoria, alem 
de que operam no espaço de usuario, enquanto processos operam no espaco de kernel/nucleo. Threads sao mais leves que processos.

Por operar no espaco do usuario, a troca de contexto entre threads eh mais rapida que entre processos, pois nao ha a necessidade
de trocar o espaco de memoria.

CURIOSIDADE: Existem threads de kernel tbm, que operam no espaco de kernel, mas sao mais pesadas que as threads de usuario.
As vantagens desse tipo de thread eh o controle de bloqueio de recursos, pois threads de usuario nao podem bloquear recursos
*/