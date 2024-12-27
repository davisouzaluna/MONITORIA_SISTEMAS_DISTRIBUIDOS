#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int create_son() {
    /*
    Primeiro vamos criar o processo filho. O fork retorna o PID do filho para o pai e 0 para o filho
    */
    int pid = fork();
    if(pid < 0) {
        perror("fork failed");
        return -1;
    }

    // Variaveis para armazenar os PIDs, tanto do pai quanto do filho, esse eh um tipo inteiro declarado em unistd.h
    pid_t father_pid, son_pid;

    if(pid == 0) {
        // Processo filho
        /*
        getpid() retorna o PID do processo atual.
        */
        son_pid = getpid();    // Armazenando o PID do filho
        father_pid = getppid(); // Armazenando o PID do pai
        printf("I'm the son. My PID is %d, and my father's PID is %d\n", son_pid, father_pid);
        return 0;
    }

    // Processo pai
    father_pid = getpid(); // Armazenando o PID do pai
    son_pid = pid;         // Armazenando o PID do filho (que é retornado pelo fork)
    printf("I'm the father. My PID is %d, and my son's PID is %d\n", father_pid, son_pid);
    return 0;
}

int main() {
    // Cria o processo pai e filho
    create_son();
    return 0;
}

/*
ordem de criacao:
    1. Processo pai
    2. Processo filho
processo pai --> fork() --> processo filho

O proccesso pai eh o proprio codigo. O processo filho eh um clone desse codigo, que a partir do 
retorno da funcao fork() ele vai executar o "if" e imprimir a mensagem na tela

*/
