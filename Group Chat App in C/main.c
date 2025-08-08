#include "main.h"

int main(void) {
  const char *ip = "127.0.0.1";
  const int port = 5050;

  int sockFD = createTCPSocket();
  if (sockFD < 0) {
    perror("socket");
    return 1;
  }

  struct sockaddr_in *address = createAddress(ip, port);

  int res = connect(sockFD, (struct sockaddr *)address, sizeof(*address));
  if (res < 0) {
    perror("connect");
    free(address);
    close(sockFD);
    return 1;
  }

  char request[] = "hello world for testing\n";
  send(sockFD, request, strlen(request), 0);

  free(address);
  close(sockFD);
  return 0;
}
