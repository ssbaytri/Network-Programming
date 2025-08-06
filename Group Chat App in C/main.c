#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(void)
{
  int sockFD = socket(AF_INET, SOCK_STREAM, 0);
  
  char *ip = "127.0.0.1";
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(5050);
  inet_pton(AF_INET, ip, &address.sin_addr.s_addr);

  int res = connect(sockFD, (struct sockaddr *)&address, sizeof(address));
  if (res == 0)
    printf("Connection was successful!\n");
  return 0;
}
