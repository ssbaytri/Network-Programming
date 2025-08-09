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
	recv(clientSockFD, buffer, 1024, 0);

	printf("Response was : %s\n", buffer);

	free(serverAddr);
	close(serverSocketFD);
	close(clientSockFD);

	return 0;
}