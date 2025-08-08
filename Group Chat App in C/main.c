#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>


int main(void)
{
  const char *ip = "google.com";
  const int port = 80;

  struct hostent *host = gethostbyname(ip);
  if (!host)
  {
    fprintf(stderr, "failed to resolve hostname\n");
    return 1;
  }

  int sockFD = socket(AF_INET, SOCK_STREAM, 0);
  if (!sockFD)
  {
    perror("socket");
    return 1;
  }
  
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);

  int res = connect(sockFD, (struct sockaddr *)&address, sizeof(address));
  if (res < 0)
  {
    perror("connect");
    close(sockFD);
    return 1;
  }

  char request[] = "GET / HTTP/1.1\r\nHost: google.com\r\nConnection: close\r\n\r\n";
  send(sockFD, request, strlen(request), 0);

  char buffer[4096];

  recv(sockFD, buffer, sizeof(buffer), 0);

  printf("%s", buffer);

  return 0;
}
