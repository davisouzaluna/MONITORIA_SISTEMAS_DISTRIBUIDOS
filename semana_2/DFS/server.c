#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "file_system.h"

#define PORT 8080
#define BUFFER_SIZE 1024

Directory *root_directory;

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        perror("Error receiving data");
        close(client_socket);
        return;
    }

    uint16_t operation = buffer[0];// Operação enviada pelo cliente
    switch (operation) {
        case 1: { //Listar arquivos
            list_files(root_directory);
            char response[BUFFER_SIZE] = "Files in root directory:\n";
            File *file = root_directory->file;
            while (file) {
                strcat(response, file->name);
                strcat(response, "\n");
                file = file->next;
            }
            send(client_socket, response, strlen(response), 0);
            break;
        }
        case 2: { //criar arquivo
            char *file_name = buffer + 1; //Nome do arquivo enviado pelo cliente
            File *new_file = create_file(file_name);
            add_file_to_directory(root_directory, new_file);
            const char *success_message = "File created successfully\n";
            send(client_socket, success_message, strlen(success_message), 0);
            break;
        }
        default:
            const char *error_message = "Unknown operation\n";
            send(client_socket, error_message, strlen(error_message), 0);
            break;
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);

    // Criar e configurar o diretório raiz com o nome menos comum possível :/
    root_directory = create_directory("root");

   
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len)) >= 0) {
        printf("Client connected\n");
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
