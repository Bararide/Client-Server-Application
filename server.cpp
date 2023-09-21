#include "server.h"

extern "C" int server(const char** facility, size_t size)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr, client;
    char buff[MAXLINE];

    ssize_t fd = open("example.txt", O_WRONLY | O_TRUNC, 0664);
    if (fd == -1)
    {
        std::cout << "open file error\n";
        return -1;
    }

    // Создание сокета
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) 
    {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        return -1;
    }

    // Настройка адреса сервера
    std::memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Привязка ко всем доступным интерфейсам
    servaddr.sin_port = htons(8090); // Порт сервера

    // Привязка сокета к адресу
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) 
    {
        std::cerr << "Ошибка при привязке сокета к адресу" << std::endl;
        return -1;
    }

    // Прослушивание входящих подключений
    if (listen(listenfd, 5) == -1) 
    {
        std::cerr << "Ошибка при прослушивании входящих подключений" << std::endl;
        return -1;
    }
    else
    {
        get_town_facility(facility, size);
        listening(client, listenfd, connfd, fd, facility, size);
    }
    close(connfd); // Закрытие сокета подключения

    return 0;
}