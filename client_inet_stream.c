#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SIZE_MSG 512
#define IP_ADDR_SND "192.168.0.123"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buf_rcv[SIZE_MSG] = {0};
    char buf_snd[SIZE_MSG] = "Hello from Client!";

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразование адреса IPv4 из текста в двоичный вид
    if (inet_pton(AF_INET, IP_ADDR_SND, &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        exit(EXIT_FAILURE);
    }

    // Подключаемся к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Отправляем сообщение
    if (send(sock, buf_snd, strlen(buf_snd), 0) < 0) {
        perror("send error");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Message sent from client\n");

    // Читаем ответ
    if (read(sock, buf_rcv, SIZE_MSG) < 0) {
        perror("read error");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Message from server: %s\n", buf_rcv);

    // Закрываем сокет
    close(sock);
    return 0;
}
