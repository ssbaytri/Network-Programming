#include "main.h"

int main()
{
	int serverSocketFD = createTCPSocket();
	struct sockaddr_in *serverAddr = createAddress("", 5050);

	int res = bind(serverSocketFD, (struct sockaddr *)serverAddr, sizeof(*serverAddr));
	if (res == 0)
		printf("socket was bound successfully!\n");

	listen(serverSocketFD, 10);

	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(struct sockaddr_in);
	int clientSockFD = accept(serverSocketFD, (struct sockaddr *)&clientAddr, &clientAddrSize);

	char buffer[1024];

	while (true)
	{
		ssize_t bytesReceived = recv(clientSockFD, buffer, sizeof(buffer) - 1, 0);

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

	free(serverAddr);
	close(serverSocketFD);
	close(clientSockFD);

	return 0;
}