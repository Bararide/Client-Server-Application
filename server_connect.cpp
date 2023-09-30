#include "server.h"
#include "error_handler.h"
#include "server_config.h"

extern "C" int server(char** data = nullptr, size_t size = 0) 
{
    Server_handler* server = new Server_handler(
            AF_INET, SOCK_STREAM, 0, AF_INET, INADDR_ANY, htons(9080)
        );


    if (listen(server->Listen_socket_fd(), 10) < 0) 
    {
        throw ERROR_THROW(102);
        return -1;
    }

    std::cout << "Сервер запущен. Ожидание подключений..." << std::endl;

    while (true) 
    {
        server->Client_socket_fd(accept(server->Listen_socket_fd(), nullptr, nullptr));

        server->Shipment_from_client(
                server->Client_socket_fd(), server->Get_setting(), sizeof(server->Get_setting())
            );
        if(data != nullptr && size != 0)
        {
            server->Forward_to_client(server->Client_socket_fd(), data, size);
        }
        else
        {
            std::cout << "Не получены данные из базы данных\n";
        }

        close(server->Client_socket_fd());
    }

    close(server->Listen_socket_fd());

    return 0;
}