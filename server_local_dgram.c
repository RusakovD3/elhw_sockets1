#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_SOCKET_PATH "/tmp/server_socket"
#define CLIENT_SOCKET_PATH "/tmp/client_socket"
#define BUF_SIZE 12

int main() {
    int socket_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer_snd[BUF_SIZE];
    char buffer_rcv[BUF_SIZE];

    // Создание сокета
    socket_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Удаление предыдущего файла сокета, если он существует
    unlink(SERVER_SOCKET_PATH);

    // Настройка адреса сокета
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_LOCAL;
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Связывание сокета с адресом
    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server waiting for messages...\n");

    // Чтение данных
    if (recvfrom(socket_fd, buffer_rcv, BUF_SIZE, 0, 
                 (struct sockaddr *)&client_addr, &client_addr_len) < 0) {
        perror("recvfrom failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s\n", buffer_rcv);

    // Настройка адреса клиента для ответа
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_LOCAL;
    strncpy(client_addr.sun_path, CLIENT_SOCKET_PATH, sizeof(client_addr.sun_path) - 1);

    // Отправка ответа
    if (sendto(socket_fd, "Hi", BUF_SIZE, 0, 
               (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("sendto failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    // Закрытие сокета
    close(socket_fd);

    return 0;
}
