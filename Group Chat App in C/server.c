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

	char buffer[1024];

	while (true)
	{
		ssize_t bytesReceived = recv(clientSock->acceptedSocketFD, buffer, sizeof(buffer) - 1, 0);

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';
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

	close(serverSocketFD);
	close(clientSock->acceptedSocketFD);
	free(serverAddr);
	free(clientSock);

	return 0;
}