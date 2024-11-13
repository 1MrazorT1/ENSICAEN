#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 1999
#define BUFFER_SIZE 1024

void send_response(SOCKET client_socket, const char *content_type, const char *content) {
    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n%s", content_type, content);
    send(client_socket, response, strlen(response), 0);
}

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

    FILE *html_file = fopen("C:/Users/1moha/Desktop/page.html", "r");
    if (html_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier HTML");
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    fseek(html_file, 0, SEEK_END);
    long file_size = ftell(html_file);
    fseek(html_file, 0, SEEK_SET);
    char *html_content = (char *)malloc(file_size + 1);
    fread(html_content, 1, file_size, html_file);
    fclose(html_file);
    html_content[file_size] = '\0';

    send_response(client_socket, "text/html", html_content);

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    free(html_content);

    return 0;
}
