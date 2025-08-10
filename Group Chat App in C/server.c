#include "main.h"

int main()
{
	int serverSocketFD = createTCPSocket();
	struct sockaddr_in *serverAddr = createAddress("", 5050);

	int res = bind(serverSocketFD, (struct sockaddr *)serverAddr, sizeof(*serverAddr));
	if (res == 0)
		printf("socket was bound successfully!\n");

	listen(serverSocketFD, 10);

	AcceptedSock* clientSock = acceptIncomingConn(serverSocketFD);

	recvAndLog(clientSock->acceptedSocketFD);

	close(serverSocketFD);
	close(clientSock->acceptedSocketFD);
	free(serverAddr);
	free(clientSock);

	return 0;
}