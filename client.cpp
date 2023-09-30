#include "client.h"

int main() 
{
    int sockfd;
    struct sockaddr_in servaddr;
    char recvline[MAXSIZE];
    char* facility[MAXSIZE];

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    // Настройка адреса сервера
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9080); // Порт сервера
    if (inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr)) <= 0)
    {
        std::cerr << "Ошибка при преобразовании IP-адреса" << std::endl;
        return 1;
    }

    // Подключение к серверу
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) 
    {
        std::cerr << "Ошибка при установлении соединения с сервером" << std::endl;
        return 1;
    }

    // Отправка данных серверу
    char buffer[MAXSIZE];
    std::cout << "Введите настройки для отправки на сервер: ";
    std::cin.getline(buffer, MAXSIZE);
    set_data_setting(buffer, sockfd);

    // Получение ответа от сервера
    buffer[MAXSIZE];
    while(true)
    {
        ssize_t res = get_data(buffer, sockfd);
        if(res != -1)
        {
            std::cout << "Данные получены\n" << buffer << std::endl;
            break;
        }
    }

    std::cout << "Получен ответ от сервера: " << buffer << std::endl;

    // Закрытие сокета
    close(sockfd);

    return 0;
}