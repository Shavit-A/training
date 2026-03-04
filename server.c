#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT (12345)
#define NUMBER_OF_CLIENTS (3)
#define BUFFER_SIZE (1024)
#define QUIT_CMD "quit"

#define VALIDATE(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "Validation failed at %s:%d\n", __FILE__, __LINE__); \
        fprintf(stderr, "Condition: %s\n", #condition); \
        fprintf(stderr, "Error [%d]: %s\n", errno, strerror(errno)); \
        return EXIT_FAILURE; \
    } \
} while (0)

typedef enum Status_s {
    SUCCESS = 0,
    FAILURE = -1
} Status;

int main(int argc, char const* const argv[])
{
    Status status = FAILURE;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    VALIDATE(server_fd != FAILURE);

    const int opt = 1;
    status = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    VALIDATE(status == SUCCESS);

    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    status = bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    VALIDATE(status == SUCCESS);

    status = listen(server_fd, NUMBER_OF_CLIENTS);
    VALIDATE(status == SUCCESS);

    printf("Waiting for client connection on port %d\n", PORT);

    struct sockaddr_in client_address = {0};
    socklen_t address_len = sizeof(client_address);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &address_len);
    VALIDATE(client_fd != FAILURE);

    printf("Client connected\n");

    char buffer[BUFFER_SIZE] = {0};
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        VALIDATE(bytes_received >= 0);
        if (bytes_received == 0) {
            printf("Client closed connection\n");
            break;
        }
        
        printf("Received: %s\n", buffer);
        
        const char* const quit_cmd = QUIT_CMD;
        if (strncmp(buffer, quit_cmd, strlen(quit_cmd)) == 0) {
            printf("Client requested to close connection\n");
            break;
        }
        
        ssize_t bytes_sent = send(client_fd, buffer, bytes_received, 0);
        VALIDATE(bytes_sent == bytes_received);
        
        printf("Echoed %ld bytes back to client\n", bytes_sent);
    }

    close(client_fd);
    close(server_fd);

    printf("Connection closed\n");
    return EXIT_SUCCESS;
}