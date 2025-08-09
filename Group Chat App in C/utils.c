#include "main.h"

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
