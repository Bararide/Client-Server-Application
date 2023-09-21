#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <vector>
#include <fstream>

#define MAXLINE 1024

using std::cin; using std::cout; using std::endl; using std::vector;

ssize_t readn(int fd, void *vptr, size_t& n);
ssize_t writen(int fd, const void* vptr, ssize_t n);

int handle_client(int connfd, ssize_t fd, const char** facility, size_t& size);
extern "C" int get_data_setting(int connfd, int fd);

extern "C" int listening(sockaddr_in& client, 
						 int& listenfd, 
						 int& connfd, 
						 ssize_t& fd, 
						 const char** facility,
						 size_t& size);

extern "C" int get_town_facility(const char** facility, size_t size);

struct package
{
    long arg1;
    long arg2;
};