#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Declarando dois mutexes
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

// Funcao que adquire mutexes na mesma ordem para evitar deadlock
void *safe_thread1(void *arg) {
    printf("Thread 1: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: Mutex1 bloqueado\n");

    // Simula algum trabalho
    sleep(1);

    printf("Thread 1: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1: Mutex2 bloqueado\n");

    // Realiza alguma operação
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void *safe_thread2(void *arg) {
    printf("Thread 2: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);  // Adquirindo mutex1 primeiro, como a Thread 1
    printf("Thread 2: Mutex1 bloqueado\n");

    // Simula algum trabalho
    sleep(1);

    printf("Thread 2: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);  // Adquirindo mutex2 depois de mutex1
    printf("Thread 2: Mutex2 bloqueado\n");

    // Realiza alguma operação
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Criando duas threads que nao causam deadlock
    pthread_create(&thread1, NULL, safe_thread1, NULL);
    pthread_create(&thread2, NULL, safe_thread2, NULL);

    // Aguardando ambas as threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

/*
Ao adquirir os mutexes na mesma ordem, evitamos o deadlock. Isso eh uma pratica comum para evitar deadlocks em sistemas com multiplos mutexes.
*/