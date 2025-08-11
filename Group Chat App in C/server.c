#include "main.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		fprintf(stderr, "Example: %s 5050\n", argv[0]);
		return 1;
  	}

	const int port = atoi(argv[1]);

	int serverSocketFD = createTCPSocket();
	struct sockaddr_in *serverAddr = createAddress("", port);

	int res = bind(serverSocketFD, (struct sockaddr *)serverAddr, sizeof(*serverAddr));
	if (res == 0)
		printf("socket was bound successfully!\n");

	listen(serverSocketFD, 10);

	startAcceptConn(serverSocketFD);

	close(serverSocketFD);
	free(serverAddr);

	return 0;
}