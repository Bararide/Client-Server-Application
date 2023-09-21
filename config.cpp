#include "client.h"

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

extern "C" int get_data(char sendline[MAXLINE], int sockfd)
{
    int size = 0;
    ssize_t read_data = readn(sockfd, &size, sizeof(size));
    if (read_data == -1)
    {
        cout << "Ошибка в получении размера\n";
        return -1;
    }
    size = ntohl(size);
    cout << size << endl;
    char** facility = new char*[size];
    for(int i = 0; i < size; ++i)
    {
        int len;
        read_data = readn(sockfd, &len, sizeof(len));
        cout << len << endl;

        facility[i] = new char[len];
        read_data = readn(sockfd, facility[i], len);
    }

    for(int i = 0; i < size; ++i)
    {
        cout << facility[i] << endl;
    }

    ssize_t fd = open("example.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if(fd == -1)
    {
        cout << "Ошибка открытия файла" << endl;
        return -1;
    }

    for(int i = 0; i < size; ++i)
    {
        char* n = "\n";
        ssize_t write_data = writen(fd, facility[i], strlen(facility[i]));
        if(write_data == -1)
        {
            cout << "Ошибка записи в файл" << endl;
            return -1;
        }
        write_data = writen(fd, n, strlen(n));
    } 
    return 1;
}

extern "C" int set_data_setting(char sendline[MAXLINE], int sockfd)
{
    struct package package;

    if(sscanf(sendline, "%ld%ld", &package.arg1, &package.arg2) != 2)
    {
        cout << "не корректные данные настроек" << endl;
        return -1;
    }
    else
    {
        ssize_t wr = writen(sockfd, &package, sizeof(package));
        if(wr == -1)
        {
            cout << "Ошибка отправки на сервер" << endl;
            return -1;
        }
    }
    return 0;
}