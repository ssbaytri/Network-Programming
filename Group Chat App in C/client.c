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

  char name[64];
  printf("Enter your name: ");
  fflush(stdout);
  if (fgets(name, sizeof(name), stdin) == NULL) {
    strcpy(name, "Anonymous");
  }
  name[strcspn(name, "\n")] = '\0';

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
      else {
        size_t nameLen = strlen(name);
        size_t lineLen = strlen(line);
        size_t composedLen = nameLen + 2 + lineLen + 1;
        char *composed = malloc(composedLen);
        if (composed == NULL) {
          perror("malloc");
          break;
        }
        snprintf(composed, composedLen, "%s: %s", name, line);
        send(sockFD, composed, strlen(composed), 0);
        free(composed);
      }
    }
  }

  {
    const char *suffix = " left the chat.\n";
    size_t composedLen = strlen(name) + strlen(suffix) + 1;
    char *leftMsg = malloc(composedLen);
    if (leftMsg) {
      snprintf(leftMsg, composedLen, "%s%s", name, suffix);
      send(sockFD, leftMsg, strlen(leftMsg), 0);
      free(leftMsg);
    }
  }

  pthread_cancel(recvThread);
  pthread_join(recvThread, NULL);

  free(address);
  close(sockFD);
  free(line);
  return 0;
}
