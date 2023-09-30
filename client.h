#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXSIZE 1024

struct package
{
    long arg1;
    long arg2;
};

int Socket(int family, int type, int protocol)
{
    int n;
    if((n = socket(family, type, protocol)) < 0)
        std::cerr << "socket error\n";

    return(n);
}

ssize_t readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    nleft = n;
    ptr = (char*)vptr;

    while(nleft > 0)
    {
        if((nread = read(fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;

        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}

ssize_t writen(int fd, const void* vptr, ssize_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char* ptr;

    ptr = (char*)vptr;
    nleft = n;
    while(nleft > 0)
    {
        if((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if(errno == EINTR)
            {
                nwritten = 0;
            }
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return(n);
}

extern "C" int set_data_setting(char sendline[MAXSIZE], int sockfd)
{
    struct package package;
    std::cout << sendline << std::endl;

    if(sscanf(sendline, "%ld%ld", &package.arg1, &package.arg2) != 2)
    {
        std::cout << "не корректные данные настроек" << std::endl;
        return -1;
    }
    else
    {
        ssize_t wr = writen(sockfd, &package, sizeof(package));
        if(wr == -1)
        {
            std::cout << "Ошибка отправки на сервер" << std::endl;
            return -1;
        }
    }
    return 0;
}

extern "C" int get_data(char sendline[MAXSIZE], int sockfd)
{
    int size = 0;
    ssize_t read_data = readn(sockfd, &size, sizeof(size));
    if (read_data == -1)
    {
        std::cout << "Ошибка в получении размера\n";
        return -1;
    }
    size = ntohl(size);
    std::cout << size << std::endl;
    char** facility = new char*[size];
    for(int i = 0; i < size; ++i)
    {
        int len;
        read_data = readn(sockfd, &len, sizeof(len));
        std::cout << len << std::endl;

        facility[i] = new char[len];
        read_data = readn(sockfd, facility[i], len);
    }

    for(int i = 0; i < size; ++i)
    {
        std::cout << facility[i] << std::endl;
    }

    ssize_t fd = open("example.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if(fd == -1)
    {
        std::cout << "Ошибка открытия файла" << std::endl;
        return -1;
    }

    for(int i = 0; i < size; ++i)
    {
        char* n = "\n";
        ssize_t write_data = writen(fd, facility[i], strlen(facility[i]));
        if(write_data == -1)
        {
            std::cout << "Ошибка записи в файл" << std::endl;
            return -1;
        }
        write_data = writen(fd, n, strlen(n));
    } 
    return 1;
}