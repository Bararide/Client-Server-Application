#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>

#define MAXLINE 1024

using std::cout;
using std::cin;
using std::endl;

ssize_t readn(int fd, void *vptr, size_t n);
ssize_t writen(int fd, const void* vptr, ssize_t n);

int Socket(int family, int type, int protocol);

extern "C" int set_data_setting(char sendline[MAXLINE], int sockfd);
extern "C" int get_data(char sendline[MAXLINE], int sockfd);

struct package
{
    long arg1;
    long arg2;
};