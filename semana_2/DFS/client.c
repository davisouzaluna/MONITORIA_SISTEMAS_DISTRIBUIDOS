#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_operation(uint16_t operation, const char *data) {
    int client_socket;
    struct sockaddr_in server_address;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE] = {0};
    buffer[0] = operation;
    if (data) {
        strncpy(buffer + 1, data, BUFFER_SIZE - 1);
    }

    if (send(client_socket, buffer, BUFFER_SIZE, 0) < 0) {
        perror("Failed to send data");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    char response[BUFFER_SIZE];
    int bytes_received = recv(client_socket, response, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        response[bytes_received] = '\0';
        printf("Response: %s\n", response);
    } else {
        perror("Failed to receive response");
    }

    close(client_socket);
}

int main() {

    printf("Sending list files operation...\n");
    send_operation(1, NULL);
    printf("Sending create file operation...\n");
    send_operation(2, "new_file.txt");
    printf("Sending list files operation...\n");
    send_operation(1, NULL);

    return 0;
}
