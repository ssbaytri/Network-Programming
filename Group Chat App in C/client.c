#include "main.h"

int main(void)
{
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

  pthread_t recvThread;
  pthread_create(&recvThread, NULL, clientIncomMsgs, &sockFD);

  char *line = NULL;
  size_t lineSize = 0;
  printf("type something here (type exit)...\n");

  while (true)
  {
    ssize_t charCount = getline(&line, &lineSize, stdin);
    
    if (charCount > 0)
    {
      if (strcmp(line, "exit\n") == 0)
        break;
      else
        send(sockFD, line, strlen(line), 0);
    }
  }

  pthread_cancel(recvThread);
  pthread_join(recvThread, NULL);

  free(address);
  close(sockFD);
  free(line);
  return 0;
}
