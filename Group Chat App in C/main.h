#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct AcceptedSock
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool accepted;
} AcceptedSock;

int createTCPSocket();
struct sockaddr_in *createAddress(const char *ip, const int port);
AcceptedSock *acceptIncomingConn(int serverSocketFD);
void *recvAndLog(void *sockFD);
void startAcceptConn(int serverSocketFD);

#endif
