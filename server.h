#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

struct Setting
{
	short arg1;
	short arg2;
};

class Server_handler
{
public:
	Server_handler();
	Server_handler(int family, int type, int protocol, int sin_family, int sin_addr, int sin_port);

	void Client_socket_fd(int acceptfd);

	int Forward_to_client(int connfd, char** data, size_t& size);
	int Shipment_from_client(int connfd, Setting& setting, int& size);
	int Shipment_from_client(int connfd, Setting&& setting, int&& size);

	int Listen_socket_fd();
	int Client_socket_fd();

	Setting Get_setting();

private:
	int listen_socket_fd;
	int client_socket_fd;

	sockaddr_in serv_addr;

	struct Setting setting;
};