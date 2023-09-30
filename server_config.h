#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

namespace SERVER_CONFIG
{
	int Create_socket(int family, int type, int protocol);

	ssize_t readn(int fd, void* vptr, size_t n);

	sockaddr_in Create_address(int sin_family, int sin_addr, int sin_port);
}