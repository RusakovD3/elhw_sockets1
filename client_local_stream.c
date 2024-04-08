#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/local_socket"

int main() {
    int socket_fd;
    struct sockaddr_un server_addr;
    char buffer[100] = {0};

    // Создание сокета
    socket_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Установка адреса сокета
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_LOCAL;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Установление соединения с сервером
    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // Отправка данных
    send(socket_fd, "Hello", 5, 0);

    // Чтение ответа
    read(socket_fd, buffer, sizeof(buffer));
    printf("Server reply: %s\n", buffer);

    // Закрытие сокета
    close(socket_fd);

    return 0;
}
