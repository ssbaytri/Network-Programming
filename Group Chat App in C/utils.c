#include "main.h"
#include <stdio.h>

int createTCPSocket()
{
	return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in *createAddress(const char *ip, const int port)
{
	struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
	address->sin_family = AF_INET;
	address->sin_port = htons(port);

	if (strlen(ip) == 0)
		address->sin_addr.s_addr = INADDR_ANY;
	else
		inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
	return address;
}

AcceptedSock *acceptIncomingConn(int serverSocketFD)
{
	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(struct sockaddr_in);
	int clientSockFD = accept(serverSocketFD, (struct sockaddr *)&clientAddr, &clientAddrSize);

	AcceptedSock* acceptedSock = malloc(sizeof(AcceptedSock));
	acceptedSock->acceptedSocketFD = clientSockFD;
	acceptedSock->address = clientAddr;
	acceptedSock->accepted = clientSockFD > 0;

	if (!acceptedSock->acceptedSocketFD)
		acceptedSock->error = clientSockFD;

	return acceptedSock;
}

AcceptedSock accptedConnections[10];
int acceptedConnCount = 0;

void broadcastMsg(char *msg, int sockFD)
{
	for (int i = 0; i < acceptedConnCount; i++)
	{
		if (accptedConnections[i].acceptedSocketFD != sockFD)
			send(accptedConnections[i].acceptedSocketFD, msg, strlen(msg), 0);
	}
}

void *recvAndLog(void *arg)
{
	char buffer[1024];
	int sockFD = *(int *)arg;

	while (true)
	{
		ssize_t bytesReceived = recv(sockFD, buffer, sizeof(buffer) - 1, 0);

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';
			printf("Response was: %s", buffer);
			broadcastMsg(buffer, sockFD);
		}
		else if (bytesReceived == 0)
		{
			printf("Client disconnected\n");
			break;
		}
		else
		{
			perror("recv");
			break;
		}
	}
	free(arg);
	close(sockFD);
	return NULL;
}

void recvAndLogOnThread(AcceptedSock *pSOcket)
{
	pthread_t id;
	int *fdCopy = malloc(sizeof(int));
	*fdCopy = pSOcket->acceptedSocketFD;
	pthread_create(&id, NULL, recvAndLog, fdCopy);
	pthread_detach(id);
	free(pSOcket);
}

void startAcceptConn(int serverSockFD)
{
    while (true)
    {
        AcceptedSock *clientSock = acceptIncomingConn(serverSockFD);
		accptedConnections[acceptedConnCount++] = *clientSock;
        recvAndLogOnThread(clientSock);
    }
}

void *clientIncomMsgs(void *arg)
{
	char buffer[1024];
	int sockFD = *(int *)arg;

	while (true)
	{
		ssize_t bytesReceived = recv(sockFD, buffer, 1024, 0);

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = 0;
			printf("Response was: %s", buffer);
		}
		else if (bytesReceived == 0)
		{
			printf("Client disconnected\n");
			break;
		}
		else
		{
			perror("recv");
			break;
		}
	}
	return NULL;
}
