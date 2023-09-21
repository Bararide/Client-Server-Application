#include "server.h"

int handle_client(int connfd, ssize_t fd, const char** facility, size_t& size)
{
    struct package package;

    ssize_t byte_read = read(connfd, &package, sizeof(package));
    if(byte_read == -1)
    {
        cout << "Ошибка при чтении данных от клиента\n";
        return -1;
    }

    int size_f = htonl(size);
    cout << size_f << endl;
    ssize_t wr = writen(connfd, &size_f, sizeof(size_f));

    for(int i = 0; i < size_f; ++i)
    {
        int len = strlen(facility[i]);
        wr = writen(connfd, &len, sizeof(len));
        if (wr == -1)
        {
            cout << "Ошибка отправки длины строки\n";
            break;
        }
        wr = writen(connfd, facility[i], len);  
        if (wr == -1)
        {
            cout << "Ошибка отправки данных\n";
            break;
        }
    }

    return 0;	
}