#include <stdio.h> //padrao para entrada(input) e saida(output)
#include <stdlib.h> //funcoes utilitarias(malloc, free, etc)
#include <string.h> //manipulacao de strings
#include <pthread.h> //criacao e manipulacao de threads
#include <unistd.h> //funcionalidades POSIX(close, fork, etc)
#include <sys/socket.h> //definicoes de socket(bind, listen, etc)
#include <netinet/in.h> //definicoes de internet(struct sockaddr_in, htons, etc)
#include <sys/un.h> //definicoes de Unix Domain Socket
#include <time.h>

//MACROS
#define PORT 4002 // Porta padrao do servidor
#define BUFFER_SIZE 1024 //tamanho padrao do buffer. Esse valor foi colocado para evitar overflow

#define MAX_CLIENTS 100 // aqui tbm nn eh um servidor meu caro, eh um servidor de teste. Se quiser aumentar a complexidade do codigo desnecessariamente fique a vontade :/
/*
Esse exemplo abaixo nao eh necessario, mas eh interessante pra caramba pra evitar os famosos IMPASSES, caso vc queira acessar um arquivo pra salvar
*/
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

#define LOG_FILE "server_log.txt" //arquivo de log
#define SOCKET_PATH "/tmp/server_socket" //caminho do socket(AF_UNIX)

/* Funcao para criar o servidor basico, utilizando TCP(AF_INET)
Foi colocado o tipo int para poder retornar um valor de erro(boas praticas)
*/
int create_srv(int port, int buffer_size);

/*
Funcao para criar o servidor local, utilizando Unix Domain Socket(AF_UNIX).

Aqui eu usei malloc pq eu nao sei o tamanho do caminho do socket. Se vc souber, pode usar um vetor de char.
*/
int create_srv_local(char *socket_path);

/*
O que vai ser salvo no arquivo de log e o identificador do cliente.

Caso o parametro log_file seja NULL, o arquivo de log vai ser o padrao(LOG_FILE) explicitada na macro
*/
void log_client_id(const char *identifier);

/*
Funcao para lidar com o cliente. Essa funcao eh a que vai ser chamada pela thread
*/
void *handle_client(void *arg);

