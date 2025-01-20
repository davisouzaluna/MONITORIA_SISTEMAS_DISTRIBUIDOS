#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_sock) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Ler requisição do cliente
    bytes_received = read(client_sock, buffer, sizeof(buffer) - 1);
    if (bytes_received < 0) {
        perror("read");
        close(client_sock);
        return;
    }

    buffer[bytes_received] = '\0'; // Null-terminate the string

    // Exibir o conteúdo da requisição
    printf("Requisição recebida:\n%s\n", buffer);

    // Resposta HTTP simples
    const char *http_response = 
        "HTTP/1.1 200 OK\r\n""Content-Type: text/html\r\n""Connection: close\r\n\r\n""<html><body><h1>Bem-vindo ao Servidor HTTP Simples!</h1><p>Como voce esta meu consagrado ?</p><p>Esse eh um servidor HTTP na versao 1, antigo pra caramba</p> </body></html>";

    write(client_sock, http_response, strlen(http_response));

    // Fechar a conexão com o cliente
    close(client_sock);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, 5) < 0) {
        perror("listen");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Servidor HTTP ouvindo na porta %d...\n", PORT);

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        printf("Conexão recebida de %s\n", inet_ntoa(client_addr.sin_addr));
        handle_request(client_sock);
    }

    close(server_sock);
    return 0;
}
