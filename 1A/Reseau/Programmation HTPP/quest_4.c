#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 1999
#define BUFFER_SIZE 1024

void extraireNomFichier(char *nom_ressource, const char* req) {
    char *req_copy = strdup(req);
    if (req_copy != NULL) {
        char *token = strtok(req_copy, " ");
        if (token != NULL) {
            token = strtok(NULL, " ");
            if (token != NULL && strcmp(token, "/") != 0) {
                strcpy(nom_ressource, token + 1);
            } else {
                strcpy(nom_ressource, "index.html");
            }
        } else {
            strcpy(nom_ressource, "");
        }
        free(req_copy);
    }
}

void send_response(SOCKET client_socket, const char *content_type, const char *content, int content_length) {
    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", content_type, content_length);
    send(client_socket, response, strlen(response), 0);
    send(client_socket, content, content_length, 0);
}

void send_error_response(SOCKET client_socket) {
    char response[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
    send(client_socket, response, strlen(response), 0);
}

const char *get_content_type(const char *filename) {
    const char *extension = strrchr(filename, '.');
    if (extension != NULL) {
        if (strcmp(extension, ".html") == 0) {
            return "text/html";
        } else if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0) {
            return "image/jpeg";
        } else if (strcmp(extension, ".gif") == 0) {
            return "image/gif";
        } else if (strcmp(extension, ".png") == 0) {
            return "image/png";
        }
    }
    return "application/octet-stream"; 
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

    int bytes_received;
    printf("Donnees recues du client: \n");
    bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);

        char nom_ressource[BUFFER_SIZE];
        extraireNomFichier(nom_ressource, buffer);

        FILE *file = fopen(nom_ressource, "rb");
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int file_size = ftell(file);
            fseek(file, 0, SEEK_SET);
            char *file_content = (char *)malloc(file_size);
            fread(file_content, 1, file_size, file);
            fclose(file);
            const char *content_type = get_content_type(nom_ressource);
            send_response(client_socket, content_type, file_content, file_size);
            free(file_content);
        } else {
            send_error_response(client_socket);
        }
    }

    if (bytes_received == SOCKET_ERROR) {
        perror("Erreur lors de la reception des donnees");
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}