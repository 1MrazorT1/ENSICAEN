#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 1999
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        perror("Erreur lors de l'initialisation de Winsock");
        return EXIT_FAILURE;
    }

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        perror("Erreur lors de la creation du socket");
        return EXIT_FAILURE;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Erreur lors du binding");
        closesocket(server_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        perror("Erreur lors de l'ecoute des connexions entrantes");
        closesocket(server_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    printf("Le serveur ecoute sur le port %d...\n", PORT);

    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == INVALID_SOCKET) {
        perror("Erreur lors de l'acceptation de la connexion entrante");
        closesocket(server_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    printf("Connexion etablie avec %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    int bytes_received;
    printf("Donnees recues du client: \n");
    do {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("%s", buffer);
        }
    } while ((bytes_received > 0) && (strchr(buffer, '\n') == NULL));

    if (bytes_received == SOCKET_ERROR) {
        perror("Erreur lors de la reception des donnees");
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}