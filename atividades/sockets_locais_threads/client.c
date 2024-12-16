#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>

#define SOCKET_PATH "/tmp/server_socket"
#define DEFAULT_TCP_PORT 8080

void generate_unique_identifier(char *buffer, size_t size) {
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, buffer);
}

int main(int argc, char *argv[]) {
    int client_socket;
    struct sockaddr_un server_addr_unix;
    struct sockaddr_in server_addr_tcp;
    char buffer_nome[37];  // UUID tem 36 caracteres + 1 para o terminador nulo
    char buffer[1024];
    
    // Verifica os argumentos passados para definir o tipo de socket
//================================== Comunicacao Unix ==================================
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <unix|tcp> [endereco_tcp] [porta_tcp]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "unix") == 0) {
        // Cria o socket para comunicação Unix
        if ((client_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
            perror("Erro ao criar socket UNIX");
            exit(EXIT_FAILURE);
        }

        memset(&server_addr_unix, 0, sizeof(server_addr_unix));
        server_addr_unix.sun_family = AF_UNIX;
        strncpy(server_addr_unix.sun_path, SOCKET_PATH, sizeof(server_addr_unix.sun_path) - 1);

        // Conecta ao servidor via socket Unix
        if (connect(client_socket, (struct sockaddr *)&server_addr_unix, sizeof(server_addr_unix)) < 0) {
            perror("Erro ao conectar ao servidor Unix");
            close(client_socket);
            exit(EXIT_FAILURE);
        }
//================================== Comunicacao TCP ==================================
    } else if (strcmp(argv[1], "tcp") == 0) {
        // Cria o socket para comunicação TCP
        if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Erro ao criar socket TCP");
            exit(EXIT_FAILURE);
        }

        memset(&server_addr_tcp, 0, sizeof(server_addr_tcp));
        server_addr_tcp.sin_family = AF_INET;
        server_addr_tcp.sin_port = htons(argc > 3 ? atoi(argv[3]) : DEFAULT_TCP_PORT); // Porta TCP
        server_addr_tcp.sin_addr.s_addr = inet_addr(argc > 2 ? argv[2] : "127.0.0.1"); // IP TCP

        // Conecta ao servidor via socket TCP
        if (connect(client_socket, (struct sockaddr *)&server_addr_tcp, sizeof(server_addr_tcp)) < 0) {
            perror("Erro ao conectar ao servidor TCP");
            close(client_socket);
            exit(EXIT_FAILURE);
        }

    } else {
        fprintf(stderr, "Tipo de socket desconhecido: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Isso é um dos identificadores
    printf("Digite seu nome: ");
    if (fgets(buffer_nome, sizeof(buffer_nome), stdin) == NULL || buffer_nome[0] == '\n') {
        generate_unique_identifier(buffer_nome, sizeof(buffer_nome));  // Se não digitar nada, gera o UUID
    } else {
        buffer_nome[strcspn(buffer_nome, "\n")] = '\0';  // Remove o newline(isso eh adicionado por padrao)
    }

    // Envia o identificador para o servidor
    if (send(client_socket, buffer_nome, strlen(buffer_nome), 0) < 0) {
        perror("Erro ao enviar identificador");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("Conectado ao servidor como: %s\n", buffer_nome);

    // Loop para enviar mensagens
    while (1) {
        printf("Digite uma mensagem (ou 'sair' para encerrar): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';  // Remove o newline

        if (strcmp(buffer, "sair") == 0) {
            printf("Encerrando cliente.\n");
            break;
        }

        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            perror("Erro ao enviar mensagem");
            break;
        }
    }

    close(client_socket);
    return 0;
}
