#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <fstream>
#include <cstring>

#define MAXLINE 1024

class Server_handler
{
public:
	Server_handler();
	Server_handler(int family, int type, int protocol, int sin_family, int sin_addr, int sin_port);

	int Listening_socket();

private:
	int client_socket_fd;
	int server_socket_fd;

	sockaddr_in serv_addr;
};