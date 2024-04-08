#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/local_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr;
    char buffer[100] = {0};

    // Создание сокета
    server_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Установка адреса сокета
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_LOCAL;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    unlink(SOCKET_PATH);

    // Связывание сокета с локальным адресом
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Прослушивание соединений
    if (listen(server_fd, 1) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s\n", SOCKET_PATH);

    // Принятие соединения
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Чтение данных
    read(client_fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);

    // Отправка ответа
    send(client_fd, "hi", 2, 0);

    // Закрытие сокетов
    close(client_fd);
    close(server_fd);

    return 0;
}
