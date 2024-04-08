#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    struct sockaddr_in serv_addr;
    char *hello = "Hello";
    char buffer[1024] = {0};
    int sock = 0;

    // Создаем файловый дескриптор сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    // Настраиваем соединение сокета
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Конвертируем IPv4 и IPv6 адреса из текста в двоичную форму
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Подключаемся к серверу на локальном хосте
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Отправляем сообщение
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Получаем ответ от сервера
    read(sock, buffer, 1024);
    printf("Message from server: %s\n", buffer);

    // Закрываем сокет
    close(sock);
    return 0;
}
