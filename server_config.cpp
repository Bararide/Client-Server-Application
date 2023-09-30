#include "error_handler.h"
#include "server.h"
#include "server_config.h"

namespace SERVER_CONFIG
{
	ssize_t readn(int fd, void* vptr, size_t n)
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

	int Create_socket(int family, int type, int protocol)
	{
		int sock = socket(family, type, protocol);
		if(sock == -1)
		{
			throw ERROR_THROW(100);
			return -1;
		}
		return (sock);
	}

	sockaddr_in Create_address(int sin_family, int sin_addr, int sin_port)
	{
		sockaddr_in addr;
		std::memset(&addr, 0, sizeof(addr));
		addr.sin_family = sin_family;
		addr.sin_addr.s_addr = sin_addr;
		addr.sin_port = sin_port;
		return addr;
	}
}