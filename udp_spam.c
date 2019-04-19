/*
 * =====================================================================================
 *
 *       Filename:  udp_spam.c
 *
 *    Description:  A traffic injection tool for testing. This tool SPAMS UDP to a 
 *                  specified host on a specified port
 *          Usage:  ./udp_spam -p <port> -h <hostname> -m <message>
 *
 * =====================================================================================

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "sock_config.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Sends the UDP packet
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
int udp_send(const char *msg, int fd, struct sockaddr_in servaddr)
{
    if (sendto(fd, msg, strlen(msg), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("cannot send message");
        return -1;
    }
    return 0;
}

void udp_spam(char* hostname, int port, char* message)
{
    int fd, n;
    struct sockaddr_in servaddr;
    const char *m;

    m = message;
    //create the UDP socket
    fd = get_udp_sock_fd();
    //configure the socket
    servaddr = configure_sock(port, hostname);
    //start spamming
    while(1) {
        udp_send(m, fd, servaddr);
        if (n++ == 1000000) {
            printf("1000000 more packets\n");
            n=0;
        }
    }
    close(fd);
} 

