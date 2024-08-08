#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SIZE_MSG 512

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buf[SIZE_MSG] = {0};
    char buf_snd[SIZE_MSG] = "Hello from serv!";

    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Установка параметров адреса
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Связывание сокета с адресом
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Ожидание входящих подключений
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Принятие входящего подключения
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    // Чтение и отправка сообщений
    memset(buf, 0, SIZE_MSG);
    if (read(new_socket, buf, SIZE_MSG) < 0) {
        perror("read error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Message from client: %s\n", buf);

    // Отправляем ответ обратно клиенту
    if (write(new_socket, buf_snd, strlen(buf_snd)) < 0){
        perror("write error");
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent\n");

    // Закрываем сокет
    close(new_socket);
    close(server_fd);

    return 0;
}
