#include "client.h"

int main(int argc, char **argv)
{

    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    char* facility[MAXLINE];

    // Создание сокета
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    // Настройка адреса сервера
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8090); // Порт сервера
    if (inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr)) <= 0)
    {
        std::cerr << "Ошибка при преобразовании IP-адреса" << std::endl;
        return 1;
    }

    // Установка соединения с сервером
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) 
    {
        std::cerr << "Ошибка при установлении соединения с сервером" << std::endl;
        return 1;
    }

    // Чтение ввода пользователя и отправка на сервер
    std::cout << "Введите настройки для отправки на сервер: ";
    std::cin.getline(sendline, MAXLINE);
    set_data_setting(sendline, sockfd);
    while(true)
    {
        ssize_t res = get_data(sendline, sockfd);
        if(res != -1)
        {
            cout << "Данные получены\n" << sendline << endl;
            break;
        }
    }
    close(sockfd);

    return 0;
}