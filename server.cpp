#include "server.h"
#include "server_config.h"
#include "error_handler.h"

Server_handler::Server_handler(int family, int type, int protocol, int sin_family, int sin_addr, int sin_protocol)
{
	listen_socket_fd = SERVER_CONFIG::Create_socket(family, type, protocol);
	serv_addr        = SERVER_CONFIG::Create_address(sin_family, sin_addr, sin_protocol);

	if(bind(listen_socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		throw std::runtime_error("Couldn't bind\n");
		//throw ERROR_THROW(101);
};

int Server_handler::Listen_socket_fd()
{
	if(listen_socket_fd == -1)
	{
		throw ERROR_THROW(100);
		return -1;
	}
	return listen_socket_fd;
};

void Server_handler::Client_socket_fd(int asseptfd)
{
    if (asseptfd < 0) throw ERROR_THROW(105);

    client_socket_fd = asseptfd;
}

int Server_handler::Client_socket_fd()
{
	return client_socket_fd;
}

Setting Server_handler::Get_setting()
{
	return setting;
}

int Server_handler::Forward_to_client(int connfd, char** data, size_t& size)
{

    int size_f = htonl(size);
    ssize_t wr = write(connfd, &size_f, sizeof(size_f));
    if(wr == -1) {throw ERROR_THROW(111); return -1; }

    for(int i = 0; i < size_f; ++i)
    {
        int len = strlen(data[i]);
        wr = write(connfd, &len, sizeof(len));
        if (wr == -1) {throw ERROR_THROW(111); return -1; }
        
        wr = write(connfd, data[i], len);  
        if (wr == -1) {throw ERROR_THROW(111); return -1; }
    }

    for(int i = 0; i < size_f; ++i)
    {
        delete[] data[i];
    }
    delete[] data;

    return 0;
}

int Server_handler::Shipment_from_client(int connfd, Setting&& setting, int&& size)
{
	ssize_t rd = read(connfd, &setting, sizeof(size));
	if(rd == -1) {throw ERROR_THROW(110); return -1;}

	std::cout << "Настройка сервера" << '\t' << setting.arg1 << setting.arg2 << std::endl;
	return 0;
}

int Server_handler::Shipment_from_client(int connfd, Setting& setting, int& size)
{
	ssize_t rd = read(connfd, &setting, sizeof(size));
	if(rd == -1) {throw ERROR_THROW(110); return -1;}

	std::cout << "Настройка сервера" << '\t' << setting.arg1 << setting.arg2 << std::endl;
	return 0;
}