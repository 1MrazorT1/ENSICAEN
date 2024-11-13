#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define MAX_LINE 1024

int main(int argc, char **argv) {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_len;
    char request[MAX_LINE];

    int port;

    if (argc != 2) {
        printf("Error: Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        sscanf(argv[1], "%d", &port);
    }

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        exit(EXIT_FAILURE);
    }

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_socket, 1) == SOCKET_ERROR) {
        printf("Listen failed\n");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    // Accept connection
    client_len = sizeof(client_addr);
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) == INVALID_SOCKET) {
        printf("Accept failed\n");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Receive and display the first line of the request
    int bytes_received = recv(client_socket, request, MAX_LINE, 0);
    if (bytes_received == SOCKET_ERROR) {
        printf("Receive failed\n");
    } else if (bytes_received == 0) {
        printf("No data received from client\n");
    } else {
        request[bytes_received] = '\0'; // Null-terminate the received data
        printf("First line of the request: %s\n", strtok(request, "\n")); // Display the first line
    }

    // Close sockets
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
