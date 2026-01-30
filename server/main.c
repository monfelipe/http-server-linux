#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main (){
    int server_fd, new_socket;
    struct sockaddr_in address;
    ssize_t valread;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET; // Define IPv4
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Força conectar o socket a porta 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Wait...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
            perror("accept");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);

        while ((valread = read(new_socket, buffer, BUFFER_SIZE - 1)) > 0) {
            buffer[valread] = '\0';
            printf("> %s\n", buffer);
        }

        if (valread < 0) {
            perror("read failed");
            close(new_socket);
            continue;
        }

        char* reply = "MTS";
        send(new_socket, reply, strlen(reply), 0);

        close(new_socket);


    }
    

    close(server_fd);
    return 0;
}
