#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define SERVER_PORT 80

#define MAXLINE 4096

#define SA struct sockaddr

void err_n_die(const char *fmt, ...);

int main(int argc, char *argv[])
{
    int     sockfd, n;
    int sendbytes;
    struct sockaddr_in serveraddr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    if (argc != 2)
    {
        err_n_die("usage:%s <server address>", argv[0]);
    }

    // Create a Socket
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("Error make scoket");
    
    // zero out the struct
    bzero( &serveraddr, sizeof(serveraddr));

    //set the socket to an internet socket
    serveraddr.sin_family = AF_INET;
    //set the server port we want to connect to
    //htons - converts endians to network standard
    serveraddr.sin_port = htons(SERVER_PORT);

    // save the input of ip address to the struct
    if(inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0)
        err_n_die("inet_pton error for %s ", argv[1]);
    
    if (connect(sockfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        err_n_die("connect failed");
    }

    printf("Connected!");
    
    return 0;
}

void err_n_die(const char* fmt, ...)
{
    int errno_save;
    va_list     ap;

    errno_save = errno;

    va_start(ap, fmt);
    vfprintf(stdout,fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);

    if (errno_save != 0)
    {
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);
    
    exit(1);
}